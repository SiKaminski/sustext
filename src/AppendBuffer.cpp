#include "AppendBuffer.h"

namespace AppendBuffer{
	void abAppend(struct abuf* ab, const void* s, int len){
		char* ptr = (char*)realloc(ab->b, ab->len + len);

		if(ptr == NULL) return;
		memcpy(&ptr[ab->len], s, len);
		ab->b = ptr;
		ab->len += len;
	}
	void abFree(struct abuf* ab){
		free(ab->b);
	}
}