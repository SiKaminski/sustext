#include "globals.h"
#include "flaghandler.h"

#include <unistd.h>
#include <stdio.h>

// SusFlags::SusFlags()
// {
//     Flags = DEFAULT_FLAGS;
// }

// SusFlags::~SusFlags() {}

namespace FlagHandler
{
    int InitFlags(int argc, char** argv)
    {
        int opt;
        while ((opt = getopt(argc, argv, ":f:srwj")) != EOF) {
            switch (opt) {
            case 'f':
                eConfig.filepath = optarg;
                Flags |= FILEIN;
                break;
            case 's':
                fprintf(stderr, "SUSSY!!!\n");
                Flags |= MODE_SUS;
                break;
           case 'r':
                fprintf(stdout, "Opening in read mode");
                 Flags |= MODE_READ;
                 break;
            case 'w':
                fprintf(stdout, "Opening in write mode");
                Flags |= MODE_WRITE;
                break;
            case ':':
                fprintf(stderr, "Option needs a value\n");
                break;
            case '?':
                fprintf(stderr, "Unknown option \'%d\'\n", optopt);
                return 0;
                break;
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