#ifndef __EDITOR_FLAGS_HPP
#define __EDITOR_FLAGS_HPP

#include "defines.hpp"
#include <unistd.h>

enum EditorFlags{
    MODE_READ   = 0x0001,
    MODE_WRITE  = 0x0002,
    MODE_SUS    = 0x0004,
    FILEIN      = 0x0008,
    FILESAVE    = 0x0010,
    
    DEFAULT_FLAGS = MODE_READ
};

// funny name ඞ
class SusFlags{
    
    public:
        struct ArgumentOutput{
            char* filepath;
        };
        uint64_t activeFlags;

        ArgumentOutput argout;

    public:
        SusFlags();
        ~SusFlags();

        /**
         * Set the flags for the given arguments
         * if none are provided then by default the editor
         * will just open in read mode for now
         * 
         * @return (int) status code
         */
        int InitFlags(int argc, char** argv);

        void SetFlags(int flags, bool on);

        /**
         * Check if a flag is enabled 
         * 
         * @param flag 
         */
        bool Enabled(int flag);
};

#endif // __EDITOR_FLAGS_HPP