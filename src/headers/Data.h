#ifndef DATA_H
#define DATA_H

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

/*** Data ***/
struct editorConfig{
	int cx, cy;
	int screenRows;
	int screenCols;
	struct termios orig_termios;
};

struct editorConfig E;
#endif // DATA_H