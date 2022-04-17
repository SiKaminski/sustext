#pragma once
#ifndef __CONFIGS_HPP
#define __CONFIGS_HPP

#include <termios.h>
#include "defines.hpp"
#include "data.hpp"

typedef struct SUSTEXT_EDITOR_SYNTAX {
	char* filetype;
	char** filematch;
	char** keywords;
	char* singleline_comment_start;
	char* multiline_comment_start;
	char* multiline_comment_end;
	int flags;
}EditorSyntax;

typedef struct SUSTEXT_EDITOR_CONFIG {
	int 	cx;
	int 	cy;  
	int 	rx;	
	int 	rowOff;
	int 	colOff;
	int 	screenRows;
	int 	screenCols;
	int 	numrows;
	erow* 	row;
	int 	dirty;		// Track amount of changes made to file
	char* 	filepath;
	char	statusmsg[80];
	time_t 	statusmsg_time;	// time out limit for status message
	EditorSyntax* syntax;
}EditorConfig;

typedef struct SUSTEXT_TERMINAL_CONFIG {
	struct termios orig_termios;
}TerminalConfig;

static char* C_HL_extensions[] = {".cpp", ".c", ".h", ".hpp", NULL};
static char* C_HL_keywords[] = {
	"switch", "if", "while", "for", "break", "continue", "return", "else",
	"struct", "union", "typedef", "static", "enum", "class", "case",

	"int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
	"void|", NULL
};
static EditorSyntax HLDB[] = {
	{
		"cpp",
		C_HL_extensions,
		C_HL_keywords,
		"//", "/*", "*/",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

#endif // __CONFIGS_HPP