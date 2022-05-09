#pragma once
#ifndef _SUSTEXT_H
#define _SUSTEXT_H

#define SUSTEXT_VERSION "v1.2.6"

#include "editor.h"
// #include "filehandler.h"

namespace Sustext
{
    void Initialize(int argc, char** argv);
};
// class Sustext{
//     public:
//     int argc;
//     char** argv;

//     SusFlags flags;
//     FileHandler filehandler;
//     Editor editor;

//     static EditorConfig E;
    
//     public:
//         Sustext(int _argc, char** _argv);
//         ~Sustext();

//         int Initialize();
// };

#endif // __SUSTEXT_H