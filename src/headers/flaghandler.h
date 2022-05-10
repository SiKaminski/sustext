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


namespace FlagHandler 
{
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
}
// // funny name ඞ
// class SusFlags
// {    
//     public:
//         struct ArgumentOutput {
//             char* filepath;
//         };
//         uint64_t activeFlags;

//         ArgumentOutput argout;

//     public:
//         SusFlags();
//         ~SusFlags();

//         /**
//          * Set the flags for the given arguments
//          * if none are provided then by default the editor
//          * will just open in read mode for now
//          * 
//          * @return (int) status code
//          */
//         int InitFlags(int argc, char** argv);

//         void SetFlags(int flags, bool on);

//         /**
//          * Check if a flag is enabled 
//          * 
//          * @param flag 
//          */
//         bool Enabled(int flag);
// };

#endif // _SUSTEXT_FLAG_HANDLER_H