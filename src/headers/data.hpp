#pragma once

#include "defines.hpp"

typedef struct erow{
	int 	size;
	int		rsize;
	char* 	chars;
	char* 	render;
	unsigned char* highlight;
}erow;

struct EditorSyntax{
	char* filetype;
	char** filematch;
	char* singleline_comment_start;
	int flags;
};

static char* C_HL_extensions[] = {".cpp", ".c", ".h", ".hpp", NULL};
static struct EditorSyntax HLDB[] = {
	{
		"cpp",
		C_HL_extensions,
		"//",
		HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
	},
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))