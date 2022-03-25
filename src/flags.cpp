#include "flags.hpp"

void SustextArgs::InitFlags(int argc, char** argv){
    int arg;
            while(arg = getopt(argc, argv, "f:s") != EOF){
        switch(arg){
            case 'f':
                argOuts.filepath = optarg;
                flags.fileIn = true;
                break;
            case 's':
                fprintf(stderr, "SUSSY!!!");
                flags.susmode = true;
                break;
        }
    }
}