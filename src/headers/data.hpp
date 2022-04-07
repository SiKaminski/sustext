#pragma once
#ifndef __DATA_HPP
#define __DATA_HPP

#include "defines.hpp"

typedef struct erow{
	int 	idx;
	int 	size;
	int		rsize;
	char* 	chars;
	char* 	render;
	unsigned char* highlight;
	int 	hl_open_comment;
}erow;

struct EditorSyntax{
	char* filetype;
	char** filematch;
	char** keywords;
	char* singleline_comment_start;
	char* multiline_comment_start;
	char* multiline_comment_end;
	int flags;
};

static char* C_HL_extensions[] = {".cpp", ".c", ".h", ".hpp", NULL};
static char* C_HL_keywords[] = {
	"switch", "if", "while", "for", "break", "continue", "return", "else",
	"struct", "union", "typedef", "static", "enum", "class", "case",

	"int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
	"void|", NULL
};
static struct EditorSyntax HLDB[] = {
	{
		"cpp",
		C_HL_extensions,
		C_HL_keywords,
		"//", "/*", "*/",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

#endif // _DATA_HPP