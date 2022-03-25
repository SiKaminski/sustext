#ifndef __IO_HPP
#define __IO_HPP

#include "defines.hpp"
#include "data.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"
#include "flags.hpp"

namespace Editor{
    static SustextArgOutputs argout;
    static SustextCmdFlags argFlags;

    /*---- INITIALIZATION ----*/
    
    /**
     * Initialize the editor functions 
     */
    void Init();

    /**
     * Initialize flags that were given as input from
     * command line (I dispise the location of this method)) 
     */
    void InitFlags(int argc, char** argv);

    /*---- ROW OPERATIONS ----*/
    
    /**
     * Append a new row onto the editor screen 
     * 
     * @param s (char*) characters in the row
     * @param len (size_t) size of the row
     */
    void AppendRow(char* s, size_t len);


    /*---- INPUTS ----*/

    /**
     * Text that will display when the editor opens a file
     * @param filename
     */
    void OpenFile(char* filename);

    /**
     * Take key input from user and move cursor accordingly 
     * @param key 
     */
    void MoveCursor(int key);

    /**
     * Take in key input from terminal and determine
     * what function to do
     */
    void ProcessKeypress();

    /*---- OUTPUTS ----*/

    /**
     * Scroll the mouse/cursor around the editor
     */
    void Scroll();

    /**
     * Prepare the inputted buffer with the next frame 
     * @param ab 
     */
	void DrawRows(struct AppendBuffer::abuf* ab);

    /**
     * Update the screen buffer 
     */
	void RefreshScreen();	
}

#endif // __IO_HPP