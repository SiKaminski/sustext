#ifndef __IO_HPP
#define __IO_HPP

#include "defines.hpp"
#include "data.hpp"
#include "appendbuffer.hpp"
#include "terminal.hpp"

namespace Editor{
    /*---- INITIALIZATION ----*/
    
    /**
     * Initialize the editor functions 
     */
    void Init();

    /*---- ROW OPERATIONS ----*/

    /**
     * Convert the cursor x position given as an input
     * int a render index 
     * 
     * @param row 
     * @param cx 
     * @return int (rx)
     */
    int RowCxToRx(erow* row, int cx);

    /**
     * fill contents of render stream 
     * 
     * @param erow 
     */
    void UpdateRow(erow* row);

    /**
     * Append a new row onto the editor screen 
     * 
     * @param s (char*) characters in the row
     * @param len (size_t) size of the row
     */
    void InsertRow(int at, char* s, size_t len);

    void InsertNewLine();

    void RowInsertChar(erow* row, int at, int c);

    void RowDeleteChar(erow* row, int at);
    
    void InsertChar(int c);

    void DeleteChar();

    void FreeRow(erow* row);

    void DeleteRow(int at);

    void RowAppendString(erow* row, char* str, size_t len);

    char* Prompt(char* prompt);

    /*---- INPUTS ----*/

    /**
     * Text that will display when the editor opens a file
     * @param filename
     */
    int OpenFile(char* filename);

    void SaveFile();

    char* RowToString(int* buflen);

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
     * Display status bar at the bottom of the screen 
     * @param ab 
     */
    void DrawStatusBar(struct AppendBuffer::abuf* ab);


    void DrawMessageBar(struct AppendBuffer::abuf* ab);

    /**
     * Update the screen buffer 
     */
	void RefreshScreen();

    void SetStatusMessage(const char* fmt...);	
}

#endif // __IO_HPP