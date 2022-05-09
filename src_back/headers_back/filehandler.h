#pragma once
#ifndef __FILEHANDLER_H
#define __FILEHANDLER_H

#include "editor.h"

class FileHandler
{
    public:
        FileHandler();
        ~FileHandler();

        int OpenFile(char* filename, Editor* editor);
        int SaveFile(Editor* editor);
};

#endif // __FILEHANDLER_H