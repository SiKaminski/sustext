#include "globals.h"
#include "flaghandler.h"
#include "Debug/logger.h"

#include <unistd.h>
#include <stdio.h>

namespace FlagHandler
{
    int Initialize(int argc, char** argv)
    {
        LOG_INFO << "Initializing flags" << std::endl; 

        int opt;
        while ((opt = getopt(argc, argv, "srwj")) != EOF) {
            switch (opt) {
                case 's':
                {
                    LOG_INFO << "SUSSY!!!\n";
                    Flags |= (int)Flag::modeSus;
                    break;
                }
                case 'r':
                {
                    LOG_INFO << "Opening in read mode\n";
                    Flags |= (int)Flag::modeRead;
                    break;
                }
                case 'w':
                {
                    LOG_INFO << "Opening in write mode\n";
                    Flags |= (int)Flag::modeWrite;
                    break;
                }
                case ':':
                {
                    LOG_WARN << "Option needs a value\n";
                    break;
                }
                case '?':
                {
                    LOG_ERROR << "Unknown option \'" << optopt << "\'\n";
                    break; 
                }    
            }
        }

        argv += optind;
        argc -= optind;

        // if there are still any arguments left, it will most likely be the file 
        if (argc == 1) {
            LOG_DEBUG << "File input: " << argv[0] << std::endl;
            eConfig.filepath = argv[0];   
            Flags |= (int)Flag::fileIn;
        }

        LOG_SUCCESS << "Initialized flags" << std::endl; 
        return 1;
    }

    bool Enabled(const Identifier identifier)
    {
        return Flags & (int)identifier;
    }
}
