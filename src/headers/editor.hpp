#pragma once
#ifndef _SUSTEXT_EDITOR_HPP_
#define _SUSTEXT_EDITOR_HPP_

#include "utils/common.hpp"
// #include <termios.h>
// #include <stddef.h>
// #include <time.h>
// #include "colors.h"
// #include "types.h"
// #include "appendbuffer.h"
// #include "structs.h"

#include <ncurses.h>
#include <stdint.h>
#include <string>

namespace Sustext
{
    enum State : int {
        HOME,
        EDIT,
        READ_ONLY,
        WELCOME,
    };

    class Editor 
    {
        struct Windows {
            WINDOW *GrettingText;
            WINDOW *Prompt;
        };

        struct Config {
            bool colorSupport;
            size_t state;
            size_t flags;
            std::string filepath;
            Mode mode;

            int rows;
            int cols;
            bool running;
            Position cursorPos;

            Windows windows;

            // int 	    rx;
            // int 	    rowOff;
            // int 	    colOff;
            // int 	    screenRows;
            // int 	    screenCols;
            // int 	    numrows;
            // RowData*    row;
            // int 	    dirty;		// Track amount of changes made to file
            // char* 	    filepath;
            // char	    statusmsg[80];
            // time_t 	    statusmsg_time;	// time out limit for status message
            // Syntax*     syntax;
            // termios     orig_termios;
        };

        Editor();
    };
// namespace Editor
// {
//     inline Config config;
//
//     /* ---------- INITIALIZATION ---------- */
//
//     /**
//      * Initialize the editor functions
//      */
//     void Initialize(int argc, char** argv);

//     //void EnableRawMode();

//     size_t DumpState(std::string filepath = "logs/editor.log");

//     void WelcomeScreen();
//     void EnterInsertMode();
//     void EnterNormalMode();
//     void EnterVisualMode();
//
//     void NormalKeyHandler(int key);
//     void NormalCommandHandler(char* cmd);
//     void InsertKeyHandler(int key);
//     void VisualKeyHandler(int key);

//     void MoveCursor(Position pos);

//     /**
//      * Display a prompt to the user on the bottom portion
//      * of the status bar
//      *
//      * @param prompt
//      * @return char*
//      */
//     //char* Prompt(const char* prompt, void(*callback)(char*, Key, Config*));
//     void DrawPrompt(std::string prompt, void(*callback)(char*, int, Config));

//     //void Find();
//
//     /**
//      * fill contents of render stream
//      *
//      * @param RowData
//      */
//     //void UpdatRowData(RowData* row);
//
//     /**
//      * Append a new row onto the editor screen
//      *
//      * @param s (char*) characters in the row
//      * @param len (size_t) size of the row
//      */
//     //void InsertRow(int pos, char* s, size_t len);
//
//     /**
//      * Update the current row with an inputted char value
//      *
//      * @param row (RowData*)
//      * @param pos position of row to insert char into
//      * @param c char to input to row
//      */
//     //void RowInsertChar(RowData* row, int pos, int c);
//
//     /**
//      * Similar to RowInsertChar but instead there is only the
//      * input of the char to add to the current row the cursor
//      * is on
//      *
//      * @param c char to insert
//      */
//     //void InsertChar(int c);
//
//     /**
//      * Depending on where the cursor is when the enter key
//      * is pressed, handle created a new line preserving
//      * the row above or splitting it to a new line depending
//      * where the cursor was placed
//      */
//     //void InsertNewLine();
//
//     /**
//      * Similar to RowInsertChar but instead you can feed a
//      * string value to be inserted into the row as a char*
//      *
//      * @param row
//      * @param str
//      * @param len
//      */
//     //void RowAppendString(RowData* row, char* str, size_t len);
//
//
//     /**
//      * Delete a row from the file while preserving the row
//      * contents above and below
//      *
//      * @param at row position to remove
//      */
//     //void DeleteRowData(int pos);
//
//     /**
//      *
//      * Remove single character from row
//      *
//      * @param row
//      * @param pos where in the row to remove char
//      */
//     //void RowDeleteChar(RowData* row, int pos);
//
//     /**
//      * remove the char from the end of a row
//      * (handy for backspace)
//      */
//     //void DeleteChar();
//
//
//     /**
//      * clear row from memory
//      *
//      * @param row
//      */
//     //void FreeRow(RowData* row);
//
//
//     //[> ---------- INPUTS ---------- <]
//
//     /**
//      * Take key input from user and move cursor accordingly
//      *
//      * @param key
//      */
//     //void MoveCursor(int key);
//
//     /**
//      * Take in key input from terminal and determine
//      * what function to do
//      */
//     void ProcessKeypress();
//
//     /**
//      * Convert the contents stored in a row to a string
//      *
//      * @param buflen
//      * @return char*
//      */
//     //char* RowToString(int* buflen);
//
//
//     //[> ---------- OUTPUTS ---------- <]
//
//     /**
//      * Scroll the mouse/cursor around the editor
//      */
//     //void Scroll();
//
//     /**
//      * Prepare the inputted buffer with the next frame
//      *
//      * @param ab
//      */
//     //void DrawRows(AppendBuffer::abuf* ab);
//
//     /**
//      * Display status bar at the bottom of the screen
//      *
//      * @param ab
//      */
//     //void DrawStatusBar(AppendBuffer::abuf* ab);
//
//     /**
//      * Display for information the user may need to see
//      * if there is further information of an action
//      * (close unsaved file, exit program, etc...)
//      *
//      * @param ab
//      */
//     //void DrawMessageBar(AppendBuffer::abuf* ab);
//
//     /**
//      * Update the screen buffer
//      */
//     void RefreshScreen();
//
//     /**
//      * Set the Status Message with a formatted string
//      *
//      * @param fmt
//      */
//     //void SetStatusMessage(const char* fmt...);
//
//     //void UpdateSyntax(RowData* row);

//     //Foreground SyntaxToColor(Highlight highlight);

//     //void SelectSyntaxHighlight();
// }
} // namespace Sustext

#endif // _SUSTEXT_EDITOR_HPP_
