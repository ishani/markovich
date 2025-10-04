package main

import (
	"bufio"
	"fmt"
	"os"

	"go.uber.org/zap"
)

const (
	trainingIoPath = "./training_data"
)

var generatedOutputs []string

// ------------------------------------------------------------------------------------------------
// dump out the trigram table
func debugDumpOccurances(pairOcc map[byte]map[byte]struct{}, content, tag string) {

	var f *os.File
	var err error

	if f, err = os.Create(fmt.Sprintf(trainingIoPath+"/debug/debug.%s.%s.json", content, tag)); err != nil {
		SysLog.Fatal("Debug dump", zap.Error(err))
	}

	defer f.Close()

	w := bufio.NewWriter(f)

	letterSorted := byteMapToSortedStrings(pairOcc)

	for _, letter := range letterSorted {

		if startsWithVowel(letter) {
			continue
		}

		fmt.Fprintf(w, "%s\n", letter)

		opmap := pairOcc[letter[0]]
		opsorted := byteMapToSortedStrings(opmap)
		{
			for _, opletter := range opsorted {

				if startsWithVowel(opletter) {
					continue
				}

				fmt.Fprintf(w, "    case '%s':   // %s%s\n", opletter, letter, opletter)
			}
		}
	}

	w.Flush()
}

var allPrefixPairOccurances map[byte]map[byte]struct{}
var allSuffixPairOccurances map[byte]map[byte]struct{}

func mergeOccuranceSet(lhs, rhs map[byte]map[byte]struct{}) {
	for k, v := range rhs {

		if lhs[k] == nil {
			lhs[k] = make(map[byte]struct{})
		}

		for k2 := range v {

			lhs[k][k2] = struct{}{}
		}
	}
}

// ------------------------------------------------------------------------------------------------
func buildAndEmit(generatedOutputPath, outputName string, trainingDataFiles ...string) {

	ft := buildFrequencyTable(trainingDataFiles...)

	mergeOccuranceSet(allPrefixPairOccurances, ft.prefixOccurances)
	mergeOccuranceSet(allSuffixPairOccurances, ft.suffixOccurances)

	debugDumpOccurances(ft.prefixOccurances, "prefix", outputName)
	debugDumpOccurances(ft.suffixOccurances, "suffix", outputName)

	// ft.DebugDumpTrigrams(outputName)

	codegenCppRoots(ft, generatedOutputPath, outputName)
	codegenCppProcessor(ft, generatedOutputPath, outputName)

	codegenJsProcessor(ft, generatedOutputPath, outputName)

	generatedOutputs = append(generatedOutputs, outputName)
}

// ------------------------------------------------------------------------------------------------
func main() {

	allPrefixPairOccurances = make(map[byte]map[byte]struct{})
	allSuffixPairOccurances = make(map[byte]map[byte]struct{})

	SysLog.Info("Starting...")

	// carve up the original data sources, export into ready-to-process training data files
	ProcessCSV("bulk/japanese_romaji.txt", "japan", 0, -1)
	ProcessCSV("bulk/uk.england.txt", "england", 0, -1)
	ProcessCSV("bulk/mixture.txt", "mix", 0, -1)

	generatedOutputPath := "../runtime/generated/"
	os.MkdirAll(generatedOutputPath, os.ModePerm)

	// load batches of training data and run code generation for each
	buildAndEmit(
		generatedOutputPath,
		"japan",
		trainingIoPath+"/processed/japan_all.txt",
	)
	buildAndEmit(
		generatedOutputPath,
		"england",
		trainingIoPath+"/processed/england_all.txt",
	)
	buildAndEmit(
		generatedOutputPath,
		"mix",
		trainingIoPath+"/processed/mix_all.txt",
	)

	codegenCppMasterInclude(generatedOutputPath, generatedOutputs...)

	debugDumpOccurances(allPrefixPairOccurances, "prefix", "global")
	debugDumpOccurances(allSuffixPairOccurances, "suffix", "global")
}
