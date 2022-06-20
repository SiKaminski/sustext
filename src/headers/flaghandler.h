#pragma once
#ifndef _SUSTEXT_FLAG_HANDLER_H
#define _SUSTEXT_FLAG_HANDLER_H

#include <stdint.h>

enum Flags {
    MODE_READ   = 0x0001,
    MODE_WRITE  = 0x0002,
    MODE_SUS    = 0x0004,
    FILEIN      = 0x0008,
    FILESAVE    = 0x0010,
    
    DEFAULT_FLAGS = MODE_READ
};

// enum FlagIdentifiers {
//     MODE_READ   = (1 << 0),
//     MODE_WRITE  = (1 << 1),
//     MODE_SUS    = (1 << 2),
//     FILEIN      = (1 << 3),
//     FILESACE    = (1 << 4)
// };


namespace FlagHandler 
{
    /**
     * Set the flags for the given arguments
     * if none are provided then by default the editor
     * will just open in read mode for now
     * 
     * @return (int) status code
     */
    int Initialize(int argc, char** argv);

    void SetFlags(int flags, bool on);

    /**
     * Check if a flag is enabled 
     * 
     * @param flag 
     */
    bool Enabled(int flag);
}

#endif // _SUSTEXT_FLAG_HANDLER_H