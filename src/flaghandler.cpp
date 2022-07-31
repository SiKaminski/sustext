#include "globals.h"
#include "flaghandler.h"
#include "Debug/logger.h"

#include <unistd.h>
#include <stdio.h>

namespace FlagHandler
{
    int Initialize(int argc, char** argv)
    {
        int opt;
        while ((opt = getopt(argc, argv, ":f:srwj")) != EOF) {
            switch (opt) {
                case 'f':
                    eConfig.filepath = optarg;
                    Flags |= (int)Flag::fileIn;
                    break;
                case 's':
                    LOG_INFO << "SUSSY!!!\n";
                    Flags |= (int)Flag::modeSus;
                    break;
                case 'r':
                    LOG_INFO << "Opening in read mode\n";
                    Flags |= (int)Flag::modeRead;
                    break;
                case 'w':
                    LOG_INFO << "Opening in write mode\n";
                    Flags |= (int)Flag::modeWrite;
                    break;
                case ':':
                    LOG_WARN << "Option needs a value\n";
                    break;
                case '?':
                    LOG_ERROR << "Unknown option \'" << optopt << "\'\n";
                    return 0;
            }
        }

        argv += optind;
        argc -= optind;

        return 1;
    }

    void SetFlags(int flags, bool on)
    {
        Flags ^= flags;
    }

    bool Enabled(int flag)
    {
        return Flags & flag;
    }
}
