#pragma once
#ifndef _SUSTEXT_FLAG_HANDLER_H_
#define _SUSTEXT_FLAG_HANDLER_H_

#include "common.h"
#include "structs.h"
#include <stdint.h>

namespace Sustext
{
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

        enum class Identifier {
            modeRead    = (1 << 0),
            modeWrite   = (1 << 1),
            modeSus     = (1 << 2),
            fileIn      = (1 << 3),
            fileSave    = (1 << 4)
        };

        /**
         * Set the flags for the given arguments
         * if none are provided then by default the editor
         * will just open in read mode for now
         * 
         * @return (int) status code
         */
        int Initialize(int argc, char** argv, Editor::Config* config);

        //void SetFlags(int flags, bool on);

        /**
         * Check if a flag is enabled 
         * 
         * @param flag 
         */
         //bool Enabled(const Identifier identifier);
    }
}

#endif // _SUSTEXT_FLAG_HANDLER_H_
