#ifndef __APPEND_BUFFER_HPP
#define __APPEND_BUFFER_HPP

#include "defines.hpp"

namespace appendbuffer{
    #define ABUF_INIT {NULL, 0}
    struct abuf{
    	char *b;
    	int len;
    };


    void abAppend(abuf *ab, const char *s, int len); 
    void abFree(abuf *ab);
}

#endif // __APPEND_BUFFER_HPP