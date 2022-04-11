#pragma once
#ifndef __CONFIGS_HPP
#define __CONFIGS_HPP

#include "defines.hpp"
#include "data.hpp"

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
	struct EditorSyntax* syntax;
}EditorConfig;

typedef struct SUSTEXT_TERMINAL_CONFIG {
	struct termios orig_termios;
}TerminalConfig;

#endif // __CONFIGS_HPP