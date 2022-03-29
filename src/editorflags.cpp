#include "editorflags.hpp"


SusFlags::SusFlags(int _argc, char** _argv){
    activeFlags = DEFAULT_FLAGS;
}

SusFlags::~SusFlags(){

}

int SusFlags::SetFlags(){
    int opt;
    while((opt = getopt(argc, argv, ":f:srwj")) != EOF){
        switch(opt){
            case 'f':
                argout.filepath = optarg;
                activeFlags |= FILEIN;
                break;
            case 's':
                fprintf(stderr, "SUSSY!!!\n");
                activeFlags |= MODE_SUS;
                break;
            case 'r':
                fprintf(stdout, "Opening in read mode");
                activeFlags |= MODE_READ;
                break;
            case 'w':
                fprintf(stdout, "Opening in write mode");
                activeFlags |= MODE_WRITE;
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
    return 1;
}

bool SusFlags::Enabled(int flag){
    return activeFlags & flag;
}