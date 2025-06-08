package main

import (
	"bytes"
	"fmt"
)

type codeGenUtil struct {
	buf       *bytes.Buffer
	path      string
	namespace string
}

func quoteCharacter(character byte) string {
	if character == '\'' {
		return "\\'"
	}
	return fmt.Sprintf("%c", character)
}

func (cg *codeGenUtil) emitSelectorCaseOpen(character byte) {
	cg.buf.WriteString("        // -- -- -- -- -- -- -- -- -- -- -- --\n")
	cg.buf.WriteString(fmt.Sprintf("        case '%s':\n", quoteCharacter(character)))
	cg.buf.WriteString("        {\n")
	cg.buf.WriteString("            switch ( trigram_u32 )\n")
	cg.buf.WriteString("            {\n")
}

func (cg *codeGenUtil) emitSelectorCaseClose(character byte) {
	cg.buf.WriteString("            } // switch _u32\n")
	cg.buf.WriteString(fmt.Sprintf("        } // %c\n", character))
	cg.buf.WriteString("        break;\n\n")
}

type sortableBranch struct {
	letter byte
	weight float32
}
