#pragma once
#ifndef __APPENDBUFFER_HPP
#define __APPENDBUFFER_HPP

#include "defines.hpp"

namespace AppendBuffer{
    #define ABUF_INIT {NULL, 0}     //Default values for null abuf struct
    
    struct abuf{
    	char *b;
    	int len;
    };

    /**
     * Append a value to a buffer with a given length 
     * 
     * @param ab (abuf*) buffer to append to
     * @param s (char*) bytes to append to buffer 
     * @param len (int) amount of bytes needed to append to the buffer
     */
    void abAppend(struct abuf *ab, const char *s, int len);

    /**
     * free buffer from memory 
     * 
     * @param ab (abuf*)
     */
    void abFree(struct abuf *ab);
}

#endif // __APPENDBUFFER_HPP