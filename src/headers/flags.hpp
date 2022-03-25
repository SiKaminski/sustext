#ifndef __SUSTEXT_FLAGS_HPP
    #define __SUSTEXT_FLAGS_HPP

#include <iostream>
#include <unistd.h>

#include "data.hpp"

#define FLAGS_INIT {false, false}
#define ARGS_INIT {nullptr}

namespace SustextArgs{
    void InitFlags(int argc, char** argv);
}

#endif // __SUSTEXT_FLAGS_HPP