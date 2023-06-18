#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_

//#include <stdint.h>
#include <iostream>
#include <bits/stdc++.h>
//#include "terminal.h"
//#include "editor.h"

//extern uint64_t Flags;
//extern Editor::Config eConfig;
//extern Terminal::Config tConfig;

namespace Sustext 
{
    enum Status {
        failure = -1,
        success = 0
    };

    namespace Editor 
    {
        enum State : int {
            Home        = 0b1,
            Edit        = 0b10,
            Readonly    = 0b100,
            Welcome     = 0b1000,
        };

        enum Mode {
            Insert,
            Visual,
            Normal
        };
    }
}

#endif // _COMMON_H_
