package main

import (
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"os"
	"sort"
	"strings"
)

// ProcessCSV takes a CSV file containing place names, extracts and conditions them ready for
// processing by the tablegen tool.
//
// It has been tested against data from geonames.org (an excellent resource for name scraping)
// http://www.geonames.org/
//
// But there are also other sources that it chews through just fine, eg
// https://obrienmedia.co.uk/blog/place-name-data-uk-towns-cities-and-villages-counties
// https://www.aggdata.com/free/spain-postal-codes
//
// inputFile is relative to the offline/training directory
// outputPrefix determines the prefix of the files that will be generated
// placeIndex is the CSV column that contains place names to extract
// subdivIndex is an optional CSV column (pass -1 to not use) that can provide separation of names
//			by, say, region or district. these are added to the output file name if present, otherwise
//			the format will be <outputPrefix>_all.txt
//
func ProcessCSV(inputFile, outputPrefix string, placeIndex, subdivIndex int) {

	filePath := fmt.Sprintf("%s/%s", trainingIoPath, inputFile)
	log.Printf("Processing %s\n", filePath)

	file, err := os.Open(filePath)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	reader := csv.NewReader(file)
	reader.ReuseRecord = true
	reader.Comment = '~'

	bySubdiv := make(map[string][]string)

	sanitizer := strings.NewReplacer(
		".", "",
		"(", "",
		")", "",
		"/", "",
		",", "",
		"!", "",
		"`", "'",
		"'s", "s",
		// brute force diacritic removal, not an exhaustive list
		"ó", "o",
		"ò", "o",
		"ñ", "n",
		"í", "i",
		"ï", "i",
		"ç", "c",
		"ü", "u",
		"ú", "u",
		"ú", "u",
		"ŭ", "u",
		"á", "a",
		"à", "a",
		"ă", "a",
		"é", "e",
		"è", "e",
	)

	for {

		record, err := reader.Read()

		if err == io.EOF {
			break
		} else if err != nil {
			log.Fatal(err)
		}

		place := strings.ToLower(record[placeIndex])

		country := "all"
		if subdivIndex >= 0 {
			country = record[subdivIndex]
		}

		// cut out characters we aren't interested in
		place = sanitizer.Replace(place)

		// for entries of the type "Hampton, West" or "Los Balsares (Altet)", first we will have
		// removed the commas or braces (above, with the sanitizer); then we cut remaining parts up by
		// splitting on spaces, each component becoming a new item to consider
		places := strings.Split(place, " ")

		// add anything over 3 letters to the pile
		for _, psep := range places {

			if len(psep) > 3 {
				bySubdiv[country] = append(bySubdiv[country], psep)
			}

		}
	}

	for k, v := range bySubdiv {

		// boil down to a list of unique entries
		uniqueEntries := make(map[string]struct{})
		for _, p := range v {
			uniqueEntries[p] = struct{}{}
		}

		// sort and strip out any invalid lines
		var keys []string
		for k := range uniqueEntries {

			// preemptive check for invalid bits, same as the main data loader will do
			if !isASCIIPrintable(k) || strings.ContainsAny(k, "0123456789\"") {
				log.Println(inputFile, " - Invalid characters found :", k)
				continue
			}

			keys = append(keys, k)
		}
		sort.Strings(keys)

		// write out the new list
		file, err := os.Create(fmt.Sprintf("%s/processed/%s_%s.txt", trainingIoPath, outputPrefix, strings.ToLower(k)))
		if err != nil {
			log.Fatal("Cannot create file", err)
		}
		defer file.Close()

		for _, p := range keys {
			fmt.Fprintln(file, p)
		}
	}
}
