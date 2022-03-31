#ifndef __FILEHANDLER_HPP
#define __FILEHANDLER_HPP

#include "editor.hpp"

class FileHandler{
    public:
        FileHandler();
        ~FileHandler();

        int OpenFile(Editor* editor);
        int SaveFile(Editor* editor);
};

#endif // __FILEHANDLER_HPP