#ifndef __IO_HPP
#define __IO_HPP

#include "defines.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"

class IO{
    public:
        IO();
        Terminal* terminal;

        /* INPUT */
        void editorMoveCursor(int key);
        void editorProcessKeypress();

        /* OUTPUT */
        void editorDrawRows(appendbuffer::abuf* ab);
        void editorRefreshScreen();
};

#endif // __IO_HPP