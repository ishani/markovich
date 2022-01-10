package main

import (
	"reflect"
	"sort"
	"unicode"
)

// ------------------------------------------------------------------------------------------------
// checks if s is ascii and printable, aka doesn't include tab, backspace, etc.
func isASCIIPrintable(s string) bool {
	for _, r := range s {
		if r > unicode.MaxASCII || !unicode.IsPrint(r) {
			return false
		}
	}
	return true
}

// ------------------------------------------------------------------------------------------------
func isVowel(c byte) bool {
	switch c {
	case 'a', 'e', 'i', 'o', 'u', 'y':
		return true
	}
	return false
}

// ------------------------------------------------------------------------------------------------
func startsWithVowel(s string) bool {
	return isVowel(s[0])
}

// ------------------------------------------------------------------------------------------------
func byteMapToSortedStrings(input interface{}) []string {

	v := reflect.ValueOf(input)
	keys := v.MapKeys()

	letterSorted := make([]string, 0, len(keys))
	for _, k := range keys {

		xr := k.Interface().(byte)
		letterSorted = append(letterSorted, string(xr))
	}
	sort.Strings(letterSorted)

	return letterSorted
}
