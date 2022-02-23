#ifndef __DATA_HPP
#define __DATA_HPP

#include "defines.hpp"

static struct EditorConfig{
    int cx, cy;
    int screenRows;
    int screenCols;
    termios orig_termios;
}E;

#endif // __DATA_HPP