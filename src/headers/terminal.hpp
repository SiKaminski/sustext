#ifndef __TERMINAL_HPP
#define __TERMINAL_HPP

#include "defines.hpp"
#include "data.hpp"

class Terminal{
    public:
        Terminal();
        void die(const char* s);
        static void disableRawMode();
        void enableRawMode();
        int editorReadKey();
        int getCursorPosition(int* rows, int* cols);
        int getWindowSize(int* rows, int* cols);
        // Terminal(); 
        // static termios orig_termios;
        // void die(const char* s);
        // static void disableRawMode();
        // void enableRawMode();
};

#endif // __TERMINAL_HPP