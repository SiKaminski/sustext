#pragma once
#ifndef _SUSTEXT_FILEHANDLER_H
#define _SUSTEXT_FILEHANDLER_H

// #include "editor.h"

// class FileHandler
// {
//     public:
//         FileHandler();
//         ~FileHandler();

//         int OpenFile(char* filename, Editor* editor);
//         int SaveFile(Editor* editor);
// };

namespace FileHandler
{
    int OpenFile(char* filename);
    int SaveFile();
}

#endif // _SUSTEXT_FILEHANDLER_H