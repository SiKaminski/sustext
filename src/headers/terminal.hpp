#pragma once
#ifndef _SUSTEXT_TERMINAL_HPP_
#define _SUSTEXT_TERMINAL_HPP_

//#include <termios.h>
//#include <ncurses.h>
//#include "editor.h"

namespace Sustext
{
    class Terminal {
    }
    //struct Config {  
        //termios OrigTermios;
        //State   state; 
    //};

    //void Initialize();

    /**
     * exit the program with a message to display what error occured 
     * 
     * @param s error message
     */
    //void die(const int severity, const char* s);

    /**
     * Put the terminal window back to the origional state it was
     * at before (from raw input to canonical mode (cooked mode)) 
     */
    //void DisableRawMode();
    
    /**
     * Enable raw input mode for the terminal by enabling and disabling
     * canonical flags
     */
    //void EnableRawMode();
    
    /**
     * Read key input 
     * 
     * @return character that was pressed 
     */
    //Editor::Key EditorReadKey();
    
    /**
     * Get the Cursor Position relative to the terminal window
     * 
     * @param rows (int) value to store row information  
     * @param cols (int) value to store column information
     * @return (int) exit status: 0 = success
     */
    //int GetCursorPosition(int* rows, int* cols);
    
    /**
     * Get the Window Size of the terminal
     * 
     * @param rows (int) value to store row information  
     * @param cols (int) value to store column information
     * @return (int) exit status: 0 = success
     */
    //int GetWindowSize(int* rows, int* cols);
}

#endif // _SUSTEXT_TERMINAL_HPP_
