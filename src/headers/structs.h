#pragma once
#ifndef _SUSTEXT_STRUCTS_H_
#define _SUSTEXT_STRUCTS_H_

#include "common.h"
#include <stdint.h>
#include <string>
#include <ncurses.h>

namespace Sustext 
{
    namespace Editor
    {
        struct Position {
            int x;
            int y;
        };

        struct Windows {
            WINDOW*     GrettingText;
            WINDOW*     Prompt; 
        };

        struct Config {
            bool        colorSupport;
            size_t      state;
            size_t      flags;
            std::string filepath;
            Mode        mode;

            int         rows;
            int         cols;  
            bool        running;
            Position    cursorPos;

            Windows     windows;

            //int 	    rx;	
            //int 	    rowOff;
            //int 	    colOff;
            //int 	    screenRows;
            //int 	    screenCols;
            //int 	    numrows;
            //RowData*    row;
            //int 	    dirty;		// Track amount of changes made to file
            //char* 	    filepath;
            //char	    statusmsg[80];
            //time_t 	    statusmsg_time;	// time out limit for status message
            //Syntax*     syntax;
            //termios     orig_termios;
        };

        //struct RowData {
            //int 	        idx;
            //int 	        size;
            //int		        rsize;
            //char* 	        chars;
            //char* 	        render;
            //byte*  highlight;
            //int 	        hl_open_comment;
        //};

        //struct Syntax {
            //char*   filetype;
            //char**  filematch;
            //char**  keywords;
            //char*   singleline_comment_start;
            //char*   multiline_comment_start;
            //char*   multiline_comment_end;
            //int     flags;
        //};
    }
}

#endif // _SUSTEXT_STRUCTS_H_
