#pragma once
#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include "utils/logger.hpp"
#define OPT [[maybe_unused]]

namespace Sustext
{
    namespace Error
    {
        enum class Severity {
            LOW,
            MEDIUM,
            HIGH, 
            FATAL,
        };

        inline void Error(Severity severity)
        {
            logger.Log(ERROR, "Exiting with severity: %d", (int)severity);
            std::exit((int)severity);
        }

        template<typename T, typename... Ts>
        inline constexpr void Error(Severity severity, T head, Ts... tail)
        {
            logger.Log(ERROR, "%s ", head);
            Error(severity, tail...);
        }
    } // namespace Error
} // namespace Sustext
#endif // _ERROR_H_
