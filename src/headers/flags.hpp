#ifndef __SUSTEXT_FLAGS_HPP
    #define __SUSTEXT_FLAGS_HPP

#include <iostream>
#include <unistd.h>

namespace SustextArgs{
    struct SustextCmdFlags{
        bool fileIn;
        bool susmode;
    };

    struct SustextArgOutputs{
        char* filepath;
    };

    static SustextCmdFlags flags;
    static SustextArgOutputs argOuts;

    void InitFlags(int argc, char** argv);
}

#endif // __SUSTEXT_FLAGS_HPP