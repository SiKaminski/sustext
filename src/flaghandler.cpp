#include "flaghandler.hpp"
#include "utils/logger.hpp"

#include <unistd.h>
#include <stdio.h>

namespace Sustext
{
    // namespace FlagHandler
    // {
    //     int Initialize(int argc, char** argv, Editor::Config* config)
    //     {
    //         logger.Log(INFO, "Initializing flags"); 
    //         config->filepath = "";

    //         int opt;
    //         while ((opt = getopt(argc, argv, "srwj")) != EOF) {
    //             switch (opt) {
    //                 case 's':
    //                 {
    //                     logger.Log(INFO, "SUSSY!!!\n");
    //                     config->flags |= (int)Flag::modeSus;
    //                     break;
    //                 }
    //                 case 'r':
    //                 {
    //                     logger.Log(INFO, "Opening in read mode\n");
    //                     config->flags |= (int)Flag::modeRead;
    //                     break;
    //                 }
    //                 case 'w':
    //                 {
    //                     logger.Log(INFO, "Opening in write mode\n");
    //                     config->flags |= (int)Flag::modeWrite;
    //                     break;
    //                 }
    //                 case ':':
    //                 {
    //                     logger.Log(WARNING, "Option needs a value\n");
    //                     break;
    //                 }
    //                 case '?':
    //                 {
    //                     logger.Log(ERROR, "Unknown option \'%d", optopt);
    //                     break; 
    //                 }    
    //             }
    //         }

    //         argv += optind;
    //         argc -= optind;

    //         // if there are still any arguments left, it will most likely be the file 
    //         if (argc == 1) {
    //             logger.Log(DEBUG, "File input: %s", argv[0]);
    //             config->filepath = argv[0];
    //             config->flags |= (int)Flag::fileIn;
    //         }

    //         logger.Log(SUCCESS, "Initialized flags"); 
    //         return success;
    //     }

    //     //bool Enabled(const Identifier identifier)
    //     //{
    //         //return *flags & (int)identifier;
    //     //}
    // }
}
