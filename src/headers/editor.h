#pragma once
#ifndef _SUSTEXT_EDITOR_H
#define _SUSTEXT_EDITOR_H

#include <termios.h>
#include <stddef.h>
#include <time.h>
#include "colors.h"
#include "appendbuffer.h"

#define CTRL_KEY(k) ((k) & 0x1f)
#define SUSTEXT_TAB_STOP 8
#define SUSTEXT_QUIT_TIMES 1

#define ROWDATA_NULL {0, 0, 0, NULL, NULL, NULL, 0}

namespace Editor 
{
	enum Keys {
		BACKSPACE = 127,
		ARROW_LEFT = 1000,
		ARROW_RIGHT,
		ARROW_UP,
		ARROW_DOWN,
		DEL_KEY,
		HOME_KEY,
		END_KEY,
		PAGE_UP,
		PAGE_DOWN
	};

    typedef struct {
	    int 	        idx;
    	int 	        size;
	    int		        rsize;
	    char* 	        chars;
	    char* 	        render;
	    unsigned char*  highlight;
	    int 	        hl_open_comment;
    } RowData;

    typedef struct {
    	char* filetype;
    	char** filematch;
    	char** keywords;
    	char* singleline_comment_start;
    	char* multiline_comment_start;
    	char* multiline_comment_end;
    	int flags;
    } Syntax;

    typedef struct {
	    int 	    cx;
	    int 	    cy;  
	    int 	    rx;	
	    int 	    rowOff;
	    int 	    colOff;
	    int 	    screenRows;
	    int 	    screenCols;
	    int 	    numrows;
	    RowData*    row;
	    int 	    dirty;		// Track amount of changes made to file
	    char* 	    filepath;
	    char	    statusmsg[80];
	    time_t 	    statusmsg_time;	// time out limit for status message
	    Syntax*     syntax;
	    struct      termios orig_termios;
    } ConfigData;
    
    /*---- INITIALIZATION ----*/
    
    /**
     * Initialize the editor functions 
    */
    void Initialize(int argc, char** argv);
    
    /**
    * Display a prompt to the user on the bottom portion
    * of the status bar 
    * 
    * @param prompt 
    * @return char* 
    */
    char* Prompt(char* prompt, void(*callback)(char*, int, Editor::ConfigData*));

    void Find();
    
    /**
     * fill contents of render stream 
    * 
    * @param RowData 
    */
    void UpdatRowData(RowData* row);
    
    /**
     * Append a new row onto the editor screen 
    * 
    * @param s (char*) characters in the row
    * @param len (size_t) size of the row
    */
    void InsertRow(int pos, char* s, size_t len);
    
    /**
     * Update the current row with an inputted char value 
    * 
    * @param row (RowData*)
    * @param pos position of row to insert char into
    * @param c char to input to row
    */
    void RowInsertChar(RowData* row, int pos, int c);
    
    /**
     * Similar to RowInsertChar but instead there is only the
    * input of the char to add to the current row the cursor
    * is on 
    * 
    * @param c char to insert
    */
    void InsertChar(int c);
    
    /**
     * Depending on where the cursor is when the enter key
    * is pressed, handle created a new line preserving
    * the row above or splitting it to a new line depending
    * where the cursor was placed 
    */
    void InsertNewLine();
    
    /**
     * Similar to RowInsertChar but instead you can feed a 
    * string value to be inserted into the row as a char* 
    * 
    * @param row
    * @param str 
    * @param len  
    */
    void RowAppendString(RowData* row, char* str, size_t len);
    
    
    /**
     * Delete a row from the file while preserving the row
    * contents above and below 
    * 
    * @param at row position to remove
    */
    void DeleteRowData(int pos);
    
    /**
     * Remove single character from row 
    * 
    * @param row 
    * @param pos where in the row to remove char
    */
    void RowDeleteChar(RowData* row, int pos);
    
    /**
     * remove the char from the end of a row
    * (handy for backspace) 
    */
    void DeleteChar();
    
    
    /**
     * clear row from memory 
    * 
    * @param row 
    */
    void FreeRow(RowData* row);
    
    
    
    /*---- INPUTS ----*/
    
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
    
    /**
    * Convert the contents stored in a row to a string 
    * 
    * @param buflen 
    * @return char* 
    */
    char* RowToString(int* buflen);
    
    
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
    
    /**
     * Display for information the user may need to see
    * if there is further information of an action
    * (close unsaved file, exit program, etc...) 
    * 
    * @param ab 
    */
    void DrawMessageBar(struct AppendBuffer::abuf* ab);
    
    /**
     * Update the screen buffer 
    */
    void RefreshScreen();
    
    /**
     * Set the Status Message with a formatted string
    * 
    * @param fmt 
    */
    void SetStatusMessage(const char* fmt...);	
    
    void UpdateSyntax(RowData* row);

    int SyntaxToColor(int highlight);

    void SelectSyntaxHighlight();
}

#endif // _SUSTEXT_EDITOR_H