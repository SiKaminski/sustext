#pragma once
#ifndef _SUSTEXT_SYNTAX_INFO_HPP
#define _SUSTEXT_SYNTAX_INFO_HPP
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "editor.h"

#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

static char* CXX_HEADER_HL_extensions[] = {".h", ".hpp", NULL};
static char* CXX_HEADER_HL_keywords[] = {
	"switch", "if", "while", "for", "break", "continue", "return", "else",
	"struct", "union", "typedef", "static", "enum", "class", "case",

	"int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
	"void|", NULL
};

static char* C_HL_extensions[] = {".c", NULL};
static char* C_HL_keywords[] = {
	"switch", "if", "while", "for", "break", "continue", "return", "else",
	"struct", "union", "typedef", "static", "enum", "class", "case",

	"int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
	"void|", NULL
};

static char* CPP_HL_extensions[] = {".cpp", NULL};
static char* CPP_HL_keywords[] = {
	"switch", "if", "while", "for", "break", "continue", "return", "else",
	"struct", "union", "typedef", "static", "enum", "class", "case",

	"int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|", "new|",
	"void|", NULL
};


static Editor::Syntax HLDB[] = {
	{
		"hpp",
		CXX_HEADER_HL_extensions,
		CXX_HEADER_HL_keywords,
		"//", "/*", "*/",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
	{
		"h",
		CXX_HEADER_HL_extensions,
		CXX_HEADER_HL_keywords,
		"//", "/*", "*/",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
	{
		"c",
		C_HL_extensions,
		C_HL_keywords,
		"//", "/*", "*/",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
	{
		"cpp",
		CPP_HL_extensions,
		CPP_HL_keywords,
		"//", "/*", "*/",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

#endif // _SUSTEXT_SYNTAX_INFO_H
