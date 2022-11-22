#pragma once
#ifndef _COMMON_H
#define _COMMON_H

//#include <stdint.h>
#include <iostream>
#include <bits/stdc++.h>
#include "logger.h"
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
            Raw         = 0b1000,
        };

        enum Mode {
            Insert,
            Visual,
            Normal
        };
    }
}

enum class Severity : int {
    unknown,
    low,
    medium,
    high,
}; 

inline void error(Severity severity)
{
    LOG_ERROR << "Exiting with severity: " << int(severity) << std::endl;
    std::cerr << '\n';
    std::exit((int)severity);
}

template<typename T, typename... Ts>
inline constexpr void error(Severity severity, T head, Ts... tail)
{
    std::cerr << head << " ";
    error(severity, tail...);
}

#endif // _COMMON_H
