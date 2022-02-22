#ifndef __OUTPUT_HPP
#define __OUTPUT_HPP

#include "defines.hpp"
#include "AppendBuffer.hpp"

namespace Output{
    void editorDrawRows(struct abuf* ab);
    void editorRefreshScreen();
}

#endif // __OUTPUT_HPP