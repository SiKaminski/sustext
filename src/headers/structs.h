#pragma once
#ifndef _SUSTEXT_STRUCTS_H
#define _SUSTEXT_STRUCTS_H

#include <stdint.h>
#include <string>

namespace Sustext 
{
    namespace Editor
    {
        struct Config {
            bool    colorSupport;
            size_t  state;
            size_t  flags;
            std::string filepath;

            int     rows;
            int     cols;  
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
    }
}

#endif // _SUSTEXT_STRUCTS_H
