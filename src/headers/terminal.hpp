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
        // Terminal(); 
        // static termios orig_termios;
        // void die(const char* s);
        // static void disableRawMode();
        // void enableRawMode();
};

#endif // __TERMINAL_HPP