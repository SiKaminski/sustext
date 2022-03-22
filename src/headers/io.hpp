#ifndef __IO_HPP
#define __IO_HPP

#include "defines.hpp"
#include "data.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"

namespace IO{
    /*---- INITIALIZATION ----*/
    
    /**
     * Initialize the editor functions 
     */
    void initEditor();

    /*---- ROW OPERATIONS ----*/
    
    /**
     * Append a new row onto the editor screen 
     * 
     * @param s (char*) characters in the row
     * @param len (size_t) size of the row
     */
    void editorAppendRow(char* s, size_t len);


    /*---- INPUTS ----*/

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

    /*---- OUTPUTS ----*/

    /**
     * Scroll the mouse/cursor around the editor
     */
    void editorScroll();

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