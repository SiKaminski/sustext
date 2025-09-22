#pragma once
#ifndef _UTILS_COMMON_HPP_
#define _UTILS_COMMON_HPP_

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
    constexpr char* VERSION     {"v1.2.6"};
    // constexpr int TAB_STOP      {4};
    // constexpr int QUIT_TIMES    {1};
    
    enum Status {
        FAILURE = -1,
        SUCESS = 0
    };

    enum Mode {
        INSERT,
        VISUAL,
        NORMAL,
    };

    struct Position {
        int X;
        int Y;
    };


    // namespace Editor 
    // {
    //     enum State : int {
    //         Home        = 0b1,
    //         Edit        = 0b10,
    //         Readonly    = 0b100,
    //         Welcome     = 0b1000,
    //     };

    //     enum Mode {
    //         Insert,
    //         Visual,
    //         Normal
    //     };
    // }
}

#endif // _UTILS_COMMON_HPP_
