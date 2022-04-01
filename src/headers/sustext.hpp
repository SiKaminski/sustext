#pragma once

#include "defines.hpp"
#include "data.hpp"
#include "terminal.hpp"
#include "appendbuffer.hpp"
#include "editor.hpp"
#include "editorflags.hpp"
#include "filehandler.hpp"
#include "configs.hpp"

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