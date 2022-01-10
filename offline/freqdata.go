package main

import (
	"bufio"
	"os"
	"sort"
	"strings"

	"go.uber.org/zap"
)

// ------------------------------------------------------------------------------------------------
type freqdata struct {
	prefixPairs         map[string]int              // stores a list of all 2-character pairs from the start of words
	prefixOccurances    map[byte]map[byte]struct{}  // char -> char occurance tree built from the prefix pairs map
	suffixPairs         map[string]int              // same as above, but for the last 2 characters of each word
	suffixOccurances    map[byte]map[byte]struct{}  //
	fragments           map[string]int              // 4-char string fragments and appearance count
	fragmentsSorted     []string                    // keys from the fragments map, sorted into an array
	fragmentsSortedJump map[byte]int                // byte->index jump table for the sorted fragments to optimise search
	trigrams            map[string]map[byte]float32 // unique trigrams with sequential character-weight lookup
	trigramsSorted      []string                    // same as above, but the trigrams map unpacked and sorted
	trigramsSortedJump  map[byte]int                // .. and again, but for trigramsSorted
}

// ------------------------------------------------------------------------------------------------
// processString takes a name from a training source and slices it into fragments
//
// a fragment is a unique 4-character chunk of a name. given a string, eg.
//      "alberto"
// we would walk it and emit "albe", "lber", "bert", "erto"
//
// .. and later those fragments, along with all the samples from all other training names,
// are used as the root trigram and potential sequential character choice; eg.
//
// "alb" -> 'e'
// "ber" -> 't' ...
//
func (fqd *freqdata) processString(log *zap.Logger, name string) {

	// tidy up and normalise case
	lowered := strings.TrimSpace(strings.ToLower(name))

	// we only consider plain ASCII text when building the tables; check that
	// this is all we have here
	if !isASCIIPrintable(lowered) || strings.ContainsAny(lowered, "0123456789\"") {
		log.Warn("Invalid characters found", zap.String("name", name))
		return
	}

	asBytes := []byte(lowered)
	byteCount := len(asBytes)
	fragmentCount := byteCount - 3

	// 4-character name minimum
	if fragmentCount <= 0 {
		log.Warn("Name too small", zap.String("name", name))
		return
	}

	// record the start and end 2-characters
	pairSlice := string(asBytes[:2])
	fqd.prefixPairs[pairSlice]++
	pairSlice = string(asBytes[byteCount-2:])
	fqd.suffixPairs[pairSlice]++

	// track how many unique fragments get added below
	prevFragments := len(fqd.fragments)

	// decompose name into 4-character chunks and store them as unique fragments
	for t := 0; t < fragmentCount; t++ {

		fragSlice := string(asBytes[t : t+4])
		fqd.fragments[fragSlice]++
	}

	log.Debug(lowered,
		zap.Int("bytes", byteCount),
		zap.Int("frags", fragmentCount),
		zap.Int("unique", len(fqd.fragments)-prevFragments),
	)
}

// ------------------------------------------------------------------------------------------------
// create the sorted acceleration structures for fragments
func (fqd *freqdata) createSortedFragments() {

	// unpack the fragment map into a sorted-by-string array
	fqd.fragmentsSorted = make([]string, 0, len(fqd.fragments))
	for k := range fqd.fragments {
		fqd.fragmentsSorted = append(fqd.fragmentsSorted, k)
	}
	sort.Strings(fqd.fragmentsSorted)

	// with the sorted array, create a jump-map that can take a leading byte
	// and return where in the sorted array that leading byte begins - used to
	// accelerate trigram searches considerably
	var lastRune byte
	for i, k := range fqd.fragmentsSorted {
		if lastRune != k[0] {
			lastRune = k[0]
			fqd.fragmentsSortedJump[lastRune] = i
		}
	}
}

// ------------------------------------------------------------------------------------------------
// once we have all the fragments recorded, we sweep through that list to create the unique
// table of trigrams and the potential sequential characters
//
// eg. if we had this (tiny) set of fragments
//
// Alla
// Anastasia
// Anastasiya
// Anatoliy
// Andriy
//
// .. and then built data for the 'ANA' trigram, we would find the following possible paths
// ANA -> S (tasia)
// ANA -> S (tasiya)
// ANA -> T (oliy)
//
// we weigh each found potential character based on how many times it was recorded, so
// in this case, 'S' is more likely to be chosen than 'T' (assuming we pay attention
// to those weights at runtime, which we don't have to, of course..)
//
// ana |
//     |-> t  ==  0.333333
//     |-> s  ==  0.666667
//
func (fqd *freqdata) buildTrigramData(log *zap.Logger, trigram string) map[byte]float32 {

	seqmap := make(map[byte]float32)

	triBytes := []byte(trigram)

	var totalCount float32

	// to narrow the search across the fragments, we start at the index
	// associated with the first byte in the trigram
	indexStart := fqd.fragmentsSortedJump[triBytes[0]]
	lastIndex := len(fqd.fragmentsSorted)

	// look through the fragments list to find matching trigrams
	// .. this is brute force, i'll worry about speed later
	for i := indexStart; i < lastIndex; i++ {

		k := fqd.fragmentsSorted[i]
		v := fqd.fragments[k]

		fragBytes := []byte(k)

		// we start with the first bytes matching and the list is sorted,
		// so as soon as they don't, we are out of options
		if fragBytes[0] != triBytes[0] {
			break
		}

		// first 3 bytes of the fragment matches the trigram we're searching for
		if fragBytes[1] == triBytes[1] &&
			fragBytes[2] == triBytes[2] {

			seqmap[fragBytes[3]] += float32(v)
			totalCount += float32(v)
		}
	}

	// rescale the recorded weights into 0..1
	totalCountRecp := 1.0 / totalCount
	for k := range seqmap {
		seqmap[k] *= totalCountRecp
	}

	return seqmap
}

// create the sorted acceleration structures for trigrams
func (fqd *freqdata) createSortedTrigrams() {

	// unpack the trigram map into a sorted-by-string array
	fqd.trigramsSorted = make([]string, 0, len(fqd.trigrams))
	for k := range fqd.trigrams {
		fqd.trigramsSorted = append(fqd.trigramsSorted, k)
	}
	sort.Strings(fqd.trigramsSorted)

	// same as the code for sorted fragments; create leading-byte jump map
	var lastRune byte
	for i, k := range fqd.trigramsSorted {
		if lastRune != k[0] {
			lastRune = k[0]
			fqd.trigramsSortedJump[lastRune] = i
		}
	}
}

type potentialAddition struct {
	letter byte
	exits  int
}

// ------------------------------------------------------------------------------------------------
// https://en.wikipedia.org/wiki/N-gram#Smoothing_techniques
//
// to try and improve the results' variance, we can try and expand out 1-branch trigrams
// so that they have additional 'pseudo branches' .. or rather, new branches built from
// existing choices rather from the training data
//
// eg. if we have ARN -> U as a 1-branch trigram
//		.. get the latter chunk of the trigram, 'RN'
//		.. and go search to see what other trigrams there are that begin with 'RN'
//				'RNA' -> ... 4 branches
//				'RNO' -> ... 2 branches
//
//		.. and select one or more of the 3rd characters as new branches
//
//		eg. ARN -> U
//			ARN -> A
//			ARN -> O
//
func (fqd *freqdata) applyOneBranchSmoothing() {

	singleBranches := 0
	smoothedSingles := 0

	for k, v := range fqd.trigrams {
		if len(v) == 1 {

			singleBranches++

			// choose 2nd and 3rd character to go match
			prefixSearch := k[1:3]

			// get the original branch byte
			var originalByte byte
			for b := range v {
				originalByte = b
			}

			indexStart := fqd.trigramsSortedJump[prefixSearch[0]]
			lastIndex := len(fqd.trigramsSorted)

			// go look through the trigrams to find ones that begin with the
			// prefixSearch string
			potentials := make([]potentialAddition, 0, 4)
			for i := indexStart; i < lastIndex; i++ {

				searchK := fqd.trigramsSorted[i]
				searchV := fqd.trigrams[k]

				numExits := len(searchV)
				triBytes := []byte(searchK)

				// run out of matching prefix items, bail out
				if prefixSearch[0] != triBytes[0] {
					break
				}
				if prefixSearch[1] == triBytes[1] {

					// ensure we aren't looking at ourselves
					potentialByte := triBytes[2]
					if potentialByte != originalByte {
						potentials = append(potentials, potentialAddition{potentialByte, numExits})
					}
				}
			}

			if len(potentials) > 0 {
				// HDD deal with the time when the original byte choice is worse
				// 		than the one we are adding - eg. a terminal
				v[potentials[0].letter] = 0.4
				v[originalByte] = 0.6

				smoothedSingles++
			}

			/*
				fmt.Println(fmt.Sprintf("%s [%s]  <= %c", k, prefixSearch, originalByte))
				for _, p := range potentials {
					fmt.Println(fmt.Sprintf(" --> [%c] %d", p.letter, p.exits))
				}
				break*/
		}
	}

	SysLog.Info("1B-Smoothing",
		zap.Int("potentials", singleBranches),
		zap.Int("smoothed", smoothedSingles),
	)
}

// ------------------------------------------------------------------------------------------------
// go unpack all the prefix and suffix 2-characters into their component parts, tracking c[0] -> c[1]
// so we can tell for a given letter, which other letters it ever appears before
func (fqd *freqdata) buildPairOccurances() {
	for pair := range fqd.prefixPairs {
		charA := pair[0]
		charB := pair[1]

		if fqd.prefixOccurances[charA] == nil {
			fqd.prefixOccurances[charA] = make(map[byte]struct{})
		}
		fqd.prefixOccurances[charA][charB] = struct{}{}
	}
	for pair := range fqd.suffixPairs {
		charA := pair[0]
		charB := pair[1]

		if fqd.suffixOccurances[charA] == nil {
			fqd.suffixOccurances[charA] = make(map[byte]struct{})
		}
		fqd.suffixOccurances[charA][charB] = struct{}{}
	}
}

// ------------------------------------------------------------------------------------------------
// given a path to a training file, build and return a completed trigram map structure
func buildFrequencyTable(paths ...string) *freqdata {

	fqd := freqdata{
		prefixPairs:         make(map[string]int),
		prefixOccurances:    make(map[byte]map[byte]struct{}),
		suffixPairs:         make(map[string]int),
		suffixOccurances:    make(map[byte]map[byte]struct{}),
		fragments:           make(map[string]int),
		fragmentsSortedJump: make(map[byte]int),
		trigrams:            make(map[string]map[byte]float32),
		trigramsSortedJump:  make(map[byte]int),
	}

	// can pass in any number of training data files to munge into a single output
	// so iterate each and add the contents into the map
	for _, path := range paths {

		freqLog := SysLog.With(
			zap.String("path", path))

		freqLog.Info("Loading training data")

		file, err := os.Open(path)
		if err != nil {
			freqLog.Fatal("Opening file", zap.Error(err))
		}
		defer file.Close()

		// go add each line from the training file to the table
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			fqd.processString(SysLog, scanner.Text())
		}

		if err := scanner.Err(); err != nil {
			freqLog.Fatal("Scanning file", zap.Error(err))
		}

	}

	// sorted fragment arrays that help speed up lookup elsewhere
	fqd.createSortedFragments()

	// finally extract the unique set of trigrams from the fragments
	for _, k := range fqd.fragmentsSorted {
		trigram := k[:3]

		if fqd.trigrams[trigram] == nil {
			fqd.trigrams[trigram] = fqd.buildTrigramData(SysLog, trigram)
		}
	}

	SysLog.Info("Stats",
		zap.Int("unique_fragments", len(fqd.fragments)),
		zap.Int("unique_trigrams", len(fqd.trigrams)),
	)

	fqd.buildPairOccurances()

	fqd.createSortedTrigrams()

	fqd.applyOneBranchSmoothing()

	return &fqd
}
