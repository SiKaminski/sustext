#pragma once

#include "defines.hpp"

namespace AppendBuffer{
    #define ABUF_INIT {NULL, 0}
    struct abuf{
    	char *b;
    	int len;
    };

    void abAppend(struct abuf *ab, const char *s, int len);
    void abFree(struct abuf *ab);
}