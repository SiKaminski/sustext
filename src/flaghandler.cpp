#include "flaghandler.h"
#include "logger.h"

#include <unistd.h>
#include <stdio.h>

namespace Sustext
{
    namespace FlagHandler
    {
        int Initialize(int argc, char** argv, Editor::Config* config)
        {
            LOG_INFO << "Initializing flags" << std::endl; 

            int opt;
            while ((opt = getopt(argc, argv, "srwj")) != EOF) {
                switch (opt) {
                    case 's':
                    {
                        LOG_INFO << "SUSSY!!!\n";
                        config->flags |= (int)Flag::modeSus;
                        break;
                    }
                    case 'r':
                    {
                        LOG_INFO << "Opening in read mode\n";
                        config->flags |= (int)Flag::modeRead;
                        break;
                    }
                    case 'w':
                    {
                        LOG_INFO << "Opening in write mode\n";
                        config->flags |= (int)Flag::modeWrite;
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
                config->filepath = argv[0];
                config->flags |= (int)Flag::fileIn;
            }

            LOG_SUCCESS << "Initialized flags" << std::endl; 
            return success;
        }

        //bool Enabled(const Identifier identifier)
        //{
            //return *flags & (int)identifier;
        //}
    }
}
