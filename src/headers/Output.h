#ifndef OUTPUT_H
#define OUTPUT_H

#include "Macros.h"
#include "Data.h"
#include "AppendBuffer.h"

namespace Output{
    void editorDrawRows(struct abuf *ab);
    void editorRefreshScreen();
}
#endif // OUTPUT_H