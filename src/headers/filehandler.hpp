#pragma once
#ifndef __FILEHANDLER_HPP
#define __FILEHANDLER_HPP

#include "defines.hpp"
#include "data.hpp"
#include "editor.hpp"
#include "configs.hpp"

class FileHandler
{
    public:
        FileHandler();
        ~FileHandler();

        int OpenFile(char* filename, Editor* editor);
        int SaveFile(Editor* editor);
};

#endif // __FILEHANDLER_HPP