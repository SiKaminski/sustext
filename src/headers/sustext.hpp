#ifndef __SUSTEXT_HPP
#define __SUSTEXT_HPP

#include "defines.hpp"
#include "terminal.hpp"

class Sustext{
    public:
        Sustext();
        Terminal terminal;
        void initEditor();
};

#endif // __SUSTEXT_HPP