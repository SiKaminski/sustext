#pragma once

#include <termios.h>

/*** Data ***/
struct editorConfig{
	int cx, cy;
	int screenRows;
	int screenCols;
	struct termios orig_termios;
};

struct editorConfig E;