#ifndef __IO_HPP
#define __IO_HPP

#include "defines.hpp"
#include "data.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"

namespace IO{

    /**
     * Initialize the editor functions 
     */
    void initEditor();

    /**
     * Text that will display when the editor opens a file
     * @param filename
     */
    void editorOpen(char* filename);

    /**
     * Take key input from user and move cursor accordingly 
     * @param key 
     */
    void editorMoveCursor(int key);

    /**
     * Take in key input from terminal and determine
     * what function to do
     */
    void editorProcessKeypress();

    /**
     * Prepare the inputted buffer with the next frame 
     * @param ab 
     */
	void editorDrawRows(struct AppendBuffer::abuf* ab);

    /**
     * Update the screen buffer 
     */
	void editorRefreshScreen();	
}

#endif // __IO_HPP