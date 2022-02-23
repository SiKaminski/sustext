#ifndef __TERMINAL_HPP
#define __TERMINAL_HPP

#include "defines.hpp"

class Terminal{
    public: 
        termios orig_termios;static 
        void die(const char* s);
        void disableRawMode();
        void enableRawMode();
};

#endif // __TERMINAL_HPP