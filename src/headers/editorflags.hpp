#ifndef __EDITOR_FLAGS_HPP
#define __EDITOR_FLAGS_HPP

#ifndef __DEFINES_HPP
    #include "defines.hpp"
#endif // __DEFINES_HPP

#include <unistd.h>

enum EditorFlags{
    MODE_READ   = 0x0001,
    MODE_WRITE  = 0x0002,
    MODE_SUS    = 0x0004,
    FILEIN      = 0x0008,
    
    DEFAULT_FLAGS = MODE_READ
};

// funny name ඞ
class SusFlags{
    
    public:
        struct ArgumentOutput{
            char* filepath;
        };
        int activeFlags;

        ArgumentOutput argout;

    public:
        SusFlags(int _argc, char** _argv);
        ~SusFlags();

        /**
         * Set the flags for the given arguments
         * if none are provided then by default the editor
         * will just open in read mode for now
         * 
         * @return (int) status code
         */
        int SetFlags();

        /**
         * Check if a flag is enabled 
         * 
         * @param flag 
         */
        bool Enabled(int flag);

    private:
        int argc;
        char** argv;
};

#endif // __EDITOR_FLAGS_HPP