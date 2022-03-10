#ifndef __DATA_HPP
#define __DATA_HPP

#include "defines.hpp"

typedef struct erow{
	int size;
	char* chars;
}erow;

struct editorConfig{
	int cx, cy;
	int screenRows;
	int screenCols;
	int numrows;
	erow row;
	struct termios orig_termios;
};

static struct editorConfig E;

#endif // __DATA_HPP