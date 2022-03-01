#pragma once

#include "defines.hpp"

/*** Data ***/
struct editorConfig{
	int cx, cy;
	int screenRows;
	int screenCols;
	struct termios orig_termios;
};

static struct editorConfig E;