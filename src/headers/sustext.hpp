#ifndef __SUSTEXT_HPP
#define __SUSTEXT_HPP

#include "defines.hpp"
#include "terminal.hpp"

class Sustext{
    public:
    struct EditorConfig{
        int cx, cy;
        int screenRows;
        int screenCols;
        termios orig_termios;
    };

    EditorConfig E;
    Terminal terminal;

    void initEditor();
};

#endif // __SUSTEXT_HPP