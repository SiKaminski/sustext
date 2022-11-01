#include "appendbuffer.h"

#include <stdlib.h>
#include <string.h>

//void AppendBuffer::abAppend(abuf* ab, const char* s, int len)
//{
	//Allocate enough memory to hold a new string in the buffer
	//char* n = (char*)realloc(ab->b, ab->len + len);
	//if (n == nullptr)
		//return;

	//// Copy len bytes of data from s -> &n[ab->len] 
	//// or in other words the end of the current data in the buffer
	//memcpy(&n[ab->len], s, len);
	//ab->b = n;
	//ab->len += len;
//}

//[> 
//very basic implementation of memory managment, will be worked on
//int the future to actually free memory better
//*/
//void AppendBuffer::abFree(abuf *ab)
//{
	//free(ab->b);
//}
