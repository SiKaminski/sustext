#pragma once

#include "defines.hpp"
#include "data.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"

namespace IO{
    void editorMoveCursor(int key);
    void editorProcessKeypress();
	void editorDrawRows(struct AppendBuffer::abuf *ab);
	void editorRefreshScreen();	
}
