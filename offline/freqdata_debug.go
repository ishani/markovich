package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"

	"go.uber.org/zap"
)

// ------------------------------------------------------------------------------------------------
// dump out the trigram table
func (tm *freqdata) DebugDumpTrigrams(tag string) {

	var f *os.File
	var err error

	if f, err = os.Create(fmt.Sprintf("debug.freqdata.%s.json", tag)); err != nil {
		SysLog.Fatal("Debug dump", zap.Error(err))
	}

	defer f.Close()

	w := bufio.NewWriter(f)

	var sortedKeys []string
	for k := range tm.trigrams {
		sortedKeys = append(sortedKeys, k)
	}
	sort.Strings(sortedKeys)

	singleBranches := 0.0

	fmt.Fprintf(w, "{\n\n")
	for _, k := range sortedKeys {

		v := tm.trigrams[k]

		var sortedWeights []int
		for b := range v {
			sortedWeights = append(sortedWeights, int(b))
		}
		sort.Ints(sortedWeights)

		fmt.Fprintf(w, "\"%s\" : {\n", k)

		addBreak := false

		if len(sortedWeights) == 1 {
			singleBranches += 1.0
		}

		for _, i := range sortedWeights {

			if addBreak {
				fmt.Fprintf(w, ",\n")
			}
			addBreak = true

			b := byte(i)
			f := v[b]
			fmt.Fprintf(w, "    \"%c\" : %f", b, f)
		}
		fmt.Fprintf(w, "\n},\n\n")
	}
	fmt.Fprintf(w, "\"total_roots\" : %d,\n", len(sortedKeys))
	fmt.Fprintf(w, "\"single_branches\" : %g,\n", singleBranches)
	fmt.Fprintf(w, "\"single_branch_pct\" : %g\n}\n", singleBranches/float64(len(sortedKeys)))

	w.Flush()
}
