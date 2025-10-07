#pragma once
#ifndef _UTILS_COMMON_HPP_
#define _UTILS_COMMON_HPP_

#include <bits/stdc++.h>

namespace Sustext 
{
    constexpr char* VERSION     {"v1.2.6"};
    constexpr int TAB_STOP      {4};
    constexpr int QUIT_TIMES    {1};
    
    enum Status {
        FAILURE = -1,
        SUCESS = 0
    };

    struct Position {
        int X;
        int Y;
    };

    namespace Editor
    {
        enum Mode {
            INSERT,
            VISUAL,
            NORMAL,
            SUS,
        };

        enum State : int {
            HOME        = 0b1,
            EDIT        = 0b10,
            READONLY    = 0b100,
            WELCOME     = 0b1000,
        };
    } // namespace Editor

    namespace Terminal
    {
        enum State : int {
            HOME        = 0b1,
            EDIT        = 0b10,
            READONLY    = 0b100,
            WELCOME     = 0b1000,
        };
    } // namespace Terminal
} // namespace Sustext

#endif // _UTILS_COMMON_HPP_
