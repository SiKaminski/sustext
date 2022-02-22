#ifndef __DATA_HPP
#define __DATA_HPP

#include "defines.hpp" 

namespace Data{
    enum editorKey{
        ARROW_LEFT = 1000,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,
        PAGE_DOWN
    };

    struct EditorConfig{
        int cx, cy;
        int screenRows;
        int screenCols;
        termios orig_termios;
    };
    EditorConfig E;
}

#endif // __DATA_HPP