#ifndef __APPEND_BUFFER_HPP
#define __APPEND_BUFFER_HPP

#include "defines.hpp"

namespace AppendBuffer{
    #define ABUF_INIT {NULL, 0}
    struct abuf{
    	char *b;
    	int len;
    };

    /**
     * Append a value to a buffer with a given length 
     * 
     * @param ab buffer to append to
     * @param s 
     * @param len 
     */
    void abAppend(struct abuf *ab, const char *s, int len);

    /**
     * free buffer from memory 
     * 
     * @param ab 
     */
    void abFree(struct abuf *ab);
}

#endif // __APPEND_BUFFER_HPP