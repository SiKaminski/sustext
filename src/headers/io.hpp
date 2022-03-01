#ifndef __IO_HPP
#define __IO_HPP

#include "defines.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"

namespace IO{
        /* INPUT */
        void editorMoveCursor(int key);
        void editorProcessKeypress(Terminal terminal);

        /* OUTPUT */
        void editorDrawRows(appendbuffer::abuf* ab);
        void editorRefreshScreen(Terminal terminal);
};

#endif // __IO_HPP