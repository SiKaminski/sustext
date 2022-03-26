#ifndef __DATA_HPP
#define __DATA_HPP

#ifndef __DEFINES_HPP
	#include "defines.hpp"
#endif // __DEFINES_HPP

typedef struct erow{
	int 	size;
	int		rsize;
	char* 	chars;
	char* 	render;
}erow;

struct editorConfig{
	int 	cx, cy, rx;
	int 	rowOff;
	int 	colOff;
	int 	screenRows;
	int 	screenCols;
	int 	numrows;
	erow* 	row;
	int 	dirty;
	char* 	filepath;
	char	statusmsg[80];
	time_t 	statusmsg_time;
	struct termios orig_termios;
};

static editorConfig E;

#endif // __DATA_HPP
