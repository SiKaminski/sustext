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

struct EditorConfig{
	int 	cx, cy, rx;	
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
	struct termios orig_termios;
};

//This kinda works
void FindCallBack(char* query, int key, EditorConfig* E);

#endif // __DATA_HPP
