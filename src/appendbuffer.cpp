#include "headers/appendbuffer.hpp"


void appendbuffer::abAppend(abuf *ab, const char *s, int len){
    char* n = (char*)realloc(ab->b, ab->len + len);

	if(n == NULL) return;
	memcpy(&n[ab->len], s, len);
	ab->b = n;
	ab->len += len;
}

void appendbuffer::abFree(abuf *ab){
	free(ab->b);
}