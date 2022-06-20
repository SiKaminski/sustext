#pragma once
#ifndef _SUSTEXT_SYNTAX_INFO_HPP
#define _SUSTEXT_SYNTAX_INFO_HPP
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "editor.h"

#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

static char* C_HL_extensions[] = {".cpp", ".c", ".h", ".hpp", NULL};
static char* C_HL_keywords[] = {
	"switch", "if", "while", "for", "break", "continue", "return", "else",
	"struct", "union", "typedef", "static", "enum", "class", "case",

	"int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
	"void|", NULL
};

static Editor::Syntax HLDB[] = {
	{
		"cpp",
		C_HL_extensions,
		C_HL_keywords,
		"//", "/*", "*/",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

#endif // _SUSTEXT_SYNTAX_INFO_H