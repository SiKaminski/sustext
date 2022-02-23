#ifndef __IO_HPP
#define __IO_HPP

#include "defines.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"
#include "sustext.hpp"

namespace IO{
    /* INPUT */
    void editorMoveCursor(int key);
    void editorProcessKeypress(Terminal* t);

    /* OUTPUT */
    void editorDrawRows(appendbuffer::abuf* ab);
    void editorRefreshScreen();
}

#endif // __IO_HPP