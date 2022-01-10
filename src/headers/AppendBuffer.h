#ifndef APPEND_BUFFER_H
#define APPEND_BUFFER_H

#include <stdlib.h>
#include <string.h>
#include <termios.h>

#define ABUF_INIT {NULL, 0}

struct abuf{
	char *b;
	int len;
};

namespace AppendBuffer{
	void abAppend(struct abuf *ab, const char *s, int len);
	void abFree(struct abuf *ab);
}

#endif // APPEND_BUFFER_H