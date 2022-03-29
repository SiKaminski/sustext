#ifndef __FILEHANDLER_HPP
#define __FILEHANDLER_HPP

#include "defines.hpp"

class FileHandler{
    public:
        FileHandler();
        ~FileHandler();

        int OpenFile(char* filename);
        int SaveFile();

    private:
          
};

#endif // __FILEHANDLER_HPP