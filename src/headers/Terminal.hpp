#ifndef __TERMINAL_HPP
#define __TERMINAL_HPP

#include "defines.hpp"
#include "Data.hpp"

namespace Terminal{
    void die(const char* s);
    void disableRawMode(Data::EditorConfig E);
    void enableRawMode(Data::EditorConfig E);
    int editorReadKey();
    int getCursorPosition(int* rows);
}

#endif // __TERMINAL_HPP