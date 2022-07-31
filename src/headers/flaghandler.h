#pragma once
#ifndef _SUSTEXT_FLAG_HANDLER_H
#define _SUSTEXT_FLAG_HANDLER_H

#include <stdint.h>


// enum FlagIdentifiers {
//     MODE_READ   = (1 << 0),
//     MODE_WRITE  = (1 << 1),
//     MODE_SUS    = (1 << 2),
//     FILEIN      = (1 << 3),
//     FILESACE    = (1 << 4)
// };


namespace FlagHandler 
{
    enum class Flag : uint64_t {
        modeRead    = 0x0001,
        modeWrite   = 0x0002,
        modeSus     = 0x0004,
        fileIn      = 0x0008,
        fileSave    = 0x0010,
        
        defaultMode = modeRead
    };

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
