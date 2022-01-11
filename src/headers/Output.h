#pragma once

#include <stdio.h>
#include <unistd.h>

#include "Macros.h"
#include "Data.h"
#include "AppendBuffer.h"

namespace Output{
    void editorDrawRows(struct abuf *ab);
    void editorRefreshScreen();
}