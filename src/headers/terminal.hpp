#ifndef __TERMINAL_HPP
#define __TERMINAL_HPP

#include "defines.hpp"
#include "data.hpp"

class Terminal{
    public:
        Terminal();
        static void die(const char* s);
        static void disableRawMode();
        void enableRawMode();
        int editorReadKey();
        int getCursorPosition(int* rows, int* cols);
        int getWindowSize(int* rows, int* cols);
};

#endif // __TERMINAL_HPP