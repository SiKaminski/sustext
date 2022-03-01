#ifndef __DATA_HPP
#define __DATA_HPP

#include "defines.hpp"

struct EditorConfig{
    int cx, cy;
    int screenRows;
    int screenCols;
    struct termios orig_termios;
};

static struct EditorConfig E;

#endif // __DATA_HPP