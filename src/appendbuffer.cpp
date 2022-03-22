#include "headers/appendbuffer.hpp"

void AppendBuffer::abAppend(struct abuf* ab, const char* s, int len){
	//Allocate enough memory to hold a new string in the buffer
	char* n = (char*)realloc(ab->b, ab->len + len);
	if(n == NULL) return;

	// Copy len bytes of data from s -> &n[ab->len] 
	// or in other words the end of the current data in the buffer
	memcpy(&n[ab->len], s, len);
	ab->b = n;
	ab->len += len;
}

/* 
very basic implementation of memory managment, will be worked on
int the future to actually free memory better
*/
void AppendBuffer::abFree(struct abuf *ab){
	free(ab->b);
}