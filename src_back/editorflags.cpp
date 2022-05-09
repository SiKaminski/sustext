#include "editorflags.h"
#include <unistd.h>
#include <stdio.h>

SusFlags::SusFlags()
{
    activeFlags = DEFAULT_FLAGS;
}

SusFlags::~SusFlags() {}

int SusFlags::InitFlags(int argc, char** argv)
{
    int opt;
    while ((opt = getopt(argc, argv, ":f:srwj")) != EOF) {
        switch (opt) {
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

void SusFlags::SetFlags(int flags, bool on)
{
    activeFlags ^= flags;
}

bool SusFlags::Enabled(int flag)
{
    return activeFlags & flag;
}