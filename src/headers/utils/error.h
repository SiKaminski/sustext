#pragma once
#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include "utils/logger.hpp"
#define OPT [[maybe_unused]]

enum class Severity {
    low,
    medium,
    high
};

inline void error(Severity severity)
{
    logger.Log(ERROR, "Exiting with severity: %d", (int)severity);
    std::exit((int)severity);
}

template<typename T, typename... Ts>
inline constexpr void error(Severity severity, T head, Ts... tail)
{
    logger.Log(ERROR, "%s ", head);
    error(severity, tail...);
}

#endif // _ERROR_H_
