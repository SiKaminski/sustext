#pragma once
#ifndef __SUSTEXT_H
#define __SUSTEXT_H

#include "editor.h"
#include "filehandler.h"

class Sustext{
    public:
    int argc;
    char** argv;

    SusFlags flags;
    FileHandler filehandler;
    Editor editor;

    static EditorConfig E;
    
    public:
        Sustext(int _argc, char** _argv);
        ~Sustext();

        int Initialize();
};

#endif // __SUSTEXT_H