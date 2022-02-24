#ifndef __SUSTEXT_HPP
#define __SUSTEXT_HPP

#include "defines.hpp"
#include "terminal.hpp"
#include "io.hpp"

class Sustext{
    public:
        Sustext();
        Terminal terminal;
        IO io;
        void initEditor();
};

#endif // __SUSTEXT_HPP