#ifndef __APPEND_BUFFER_HPP
#define __APPEND_BUFFER_HPP

namespace AppendBuffer{
    #define ABUF_INIT {NULL, 0}
    struct abuf{
        char* b;
        int len;
    };

    void abAppend(abuf* ab, const char* s, int len);
    void abFree(abuf* ab);
}

#endif //__APPEND_BUFFER_HPP