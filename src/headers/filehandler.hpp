#pragma once

#include "defines.hpp"
#include "data.hpp"
#include "editor.hpp"
#include "configs.hpp"

class FileHandler{
    public:
        FileHandler();
        ~FileHandler();

        int OpenFile(char* filename, Editor* editor);
        int SaveFile(Editor* editor);
};