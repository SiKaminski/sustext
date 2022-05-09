#include "globals.h"
#include "editor.h"

#include <ctype.h>
// #include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/ioctl.h>
#include <unistd.h>
// #include <termios.h>
// #include <sys/types.h>
#include <time.h>
#include <stdarg.h>
// #include <fcntl.h>

namespace Editor
{
    void Initialize(int argc, char** argv)
    {
    	eConfig.cx = 0;
    	eConfig.cy = 0;
    	eConfig.rx = 0;
    	eConfig.rowOff = 0;
    	eConfig.colOff = 0;
    	eConfig.numrows = 0;
    	eConfig.row = new RowData{0, 0, NULL, NULL};
    	eConfig.filepath = NULL;
    	eConfig.statusmsg[0] = '\0';
    	// eConfig.statusmsg_time = 0;
    	eConfig.dirty = 0;
    	// eConfig.syntax = NULL;

    	if (Terminal::getWindowSize(&eConfig.screenRows, &eConfig.screenCols) == -1) 
    		Terminal::die("getWindowSize");
	
    	eConfig.screenRows -= 2; //Account for status bar sapce so it won't be drawn over
    }

    /*---- ROW OPERATIONS ----*/
    int RowCxToRx(RowData* row, int cx)
    {
        int rx = 0;
        for (int i = 0; i < cx; i++) {
            // Check to see how many columns to the left of the next tab the cursor is
            if (row->chars[i] == '\t')
                rx += (SUSTEXT_TAB_STOP - 1) - (rx % SUSTEXT_TAB_STOP);

            rx++;
        }

        return rx;
    }

    int RowRxToCx(RowData* row, int rx)
    {
        int curRx = 0;
        int cx;
        for (cx = 0; cx < row->size; cx++) {
            if (row->chars[cx] == '\t')
                curRx += (SUSTEXT_TAB_STOP - 1) - (curRx % SUSTEXT_TAB_STOP);

            curRx++;
            if (curRx > rx)
                return cx;
        }

        return cx;
    }

    int isSeperator(int c)
    {
        return isspace(c) || c == '\0' || strchr(",.()+-/*=~%<>[];", c) != NULL;
    }

    // char *Prompt(char *prompt, void (*callback)(char *query, int key, EditorConfig *))
    // {
    //     size_t bufsize = 128;
    //     char *buf = (char *)malloc(bufsize);

    //     size_t buflen = 0;
    //     buf[0] = '\0';

    //     while (1) {
    //         SetStatusMessage(prompt, buf);
    //         RefreshScreen();

    //         int c = Terminal::editorReadKey();

    //         // Check if user is removing a character
    //         if (c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE) {
    //             if (buflen != 0)
    //                 buf[--buflen] = '\0';
    //         } else if (c == '\x1b') {
    //             SetStatusMessage("");
    //             if (callback)
    //                 callback(buf, c, &E);

    //             free(buf);
    //             return NULL;
    //         } else if (c == '\r') {
    //             if (buflen != 0) {
    //                 SetStatusMessage("");
    //                 if (callback)
    //                     callback(buf, c, &E);

    //                 return buf;
    //             }
    //         } else if (!iscntrl(c) && c < 128) {
    //             if (buflen == bufsize - 1) {
    //                 bufsize *= 2;
    //                 buf = (char *)realloc(buf, bufsize);
    //             }

    //             buf[buflen++] = c;
    //             buf[buflen] = '\0';
    //         }

    //         if (callback)
    //             callback(buf, c, &E);
    //     }
    // }

    // void FindCallBack(char *query, int key, EditorConfig *E)
    // {
    //     static int lastMatch = -1;
    //     static int direction = 1;
    //     static int savedHighlightLine;
    //     static char *savedHighlight = NULL;

    //     if (savedHighlight) {
    //         memcpy(E->row[savedHighlightLine].highlight, savedHighlight, E->row[savedHighlightLine].rsize);
    //         free(savedHighlight);
    //         savedHighlight = NULL;
    //     }

    //     if (key == '\r' || key == '\x1b') {
    //         lastMatch = -1;
    //         direction = 1;
    //     } else if (key == ARROW_RIGHT || key == ARROW_DOWN) {
    //         direction = 1;
    //     } else if (key == ARROW_LEFT || key == ARROW_UP) {
    //         direction = 1;
    //     } else {
    //         lastMatch = -1;
    //         direction = 1;
    //     }

    //     if (lastMatch == -1)
    //         direction = 1;

    //     int current = lastMatch;
    //     for (int i = 0; i < E->numrows; i++) {
    //         current += direction;

    //         if (current == -1)
    //             current = E->numrows - 1;
    //         else if (current == E->numrows)
    //             current = 0;

    //         RowData *row = &E->row[current];
    //         char *match = strstr(row->render, query);
    //         if (match) {
    //             lastMatch = current;
    //             E->cy = current;
    //             E->cx = RowRxToCx(row, match - row->render);
    //             E->rowOff = E->numrows;

    //             savedHighlightLine = current;
    //             savedHighlight = (char *)malloc(row->rsize);
    //             memcpy(savedHighlight, row->highlight, row->rsize);
    //             memset(&row->highlight[match - row->render], HL_MATCH, strlen(query));
    //             break;
    //         }
    //     }
    // }

    // void Find()
    // {
    //     int savedCx = eConfig.cx;
    //     int savedCy = eConfig.cy;
    //     int savedColOff = eConfig.colOff;
    //     int savedRowOff = eConfig.rowOff;

    //     char *query = Prompt("Search -> %s (ESC to cancel)", FindCallBack);

    //     if (query) {
    //         free(query);
    //     } else {
    //         eConfig.cx = savedCx;
    //         eConfig.cy = savedCy;
    //         eConfig.colOff = savedColOff;
    //         eConfig.rowOff = savedRowOff;
    //     }
    // }

    void UpdateRow(RowData* row) 
    {
        int tabs = 0;
        for (int j = 0; j < row->size; j++) {
            if (row->chars[j] == '\t')
                tabs++;
        }

        free(row->render);
        row->render = (char*)malloc(row->size + tabs * (SUSTEXT_TAB_STOP - 1) + 1);

        int i = 0;
        for (int j = 0; j < row->size; j++) {
            if (row->chars[j] == '\t') {
                row->render[i++] = ' ';
                while (i % SUSTEXT_TAB_STOP != 0) {
                    row->render[i++] = ' ';
                }
            } else {
                row->render[i++] = row->chars[j];
            }
        }

        row->render[i] = '\0';
        row->rsize = i;

        UpdateSyntax(row);
    }

    void InsertRow(int at, char* s, size_t len)
    {
        if (at < 0 || at > eConfig.numrows)
            return;

        eConfig.row = (RowData*)realloc(eConfig.row, sizeof(RowData) * (eConfig.numrows + 1));
        memmove(&eConfig.row[at + 1], &eConfig.row[at], sizeof(RowData) * (eConfig.numrows - at));
        for (int i = at + 1; i <= eConfig.numrows; i++) {
            eConfig.row[i].idx++;
        }

        eConfig.row[at].idx = at;
        eConfig.row[at].size = len;
        eConfig.row[at].chars = (char *)malloc(len + 1);

        memcpy(eConfig.row[at].chars, s, len);
        eConfig.row[at].chars[len] = '\0';

        // Initialize render for buffer
        eConfig.row[at].rsize = 0;
        eConfig.row[at].render = NULL;
        eConfig.row[at].highlight = NULL;
        eConfig.row[at].hl_open_comment = 0;
        UpdateRow(&eConfig.row[at]);

        eConfig.numrows++;
        eConfig.dirty++;
    }

    void RowInsertChar(RowData* row, int at, int c)
    {
        if (at < 0 || at > row->size)
            at = row->size;

        row->chars = (char*)realloc(row->chars, row->size + 2);
        memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);
        row->size++;
        row->chars[at] = c;
        UpdateRow(row);
        eConfig.dirty++;
    }

    void InsertChar(int c)
    {
        if (eConfig.cy == eConfig.numrows)
            InsertRow(eConfig.numrows, (char*)"", 0);

        RowInsertChar(&eConfig.row[eConfig.cy], eConfig.cx, c);
        eConfig.cx++;
    }

    void InsertNewLine()
    {
        if (eConfig.cx == 0) {
            InsertRow(eConfig.cy, (char *)"", 0);
        } else {
            RowData *row = &eConfig.row[eConfig.cy];
            InsertRow(eConfig.cy + 1, &row->chars[eConfig.cx], row->size - eConfig.cx);
            row = &eConfig.row[eConfig.cy];
            row->size = eConfig.cx;
            row->chars[row->size] = '\0';
            UpdateRow(row);
        }

        eConfig.cy++;
        eConfig.cx = 0;
    }

    void RowAppendString(RowData* row, char* str, size_t len)
    {
        row->chars = (char*)realloc(row->chars, row->size + len + 1);
        memcpy(&row->chars[row->size], str, len);
        row->size += len;
        row->chars[row->size] = '\0';
        UpdateRow(row);
        eConfig.dirty++;
    }

    void DeleteRow(int at)
    {
        if (at < 0 || at >= eConfig.numrows)
            return;

        FreeRow(&eConfig.row[at]);
        memmove(&eConfig.row[at], &eConfig.row[at + 1], sizeof(RowData) * (eConfig.numrows - at - 1));
        for (int i = at; eConfig.numrows - 1; i++) {
            eConfig.row[i].idx--;
        }

        eConfig.numrows--;
        eConfig.dirty++;
    }

    void RowDeleteChar(RowData *row, int at)
    {
        if (at < 0 || at >= row->size)
            return;

        memmove(&row->chars[at], &row->chars[at + 1], row->size - at);
        row->size--;
        UpdateRow(row);
        eConfig.dirty++;
    }

    void DeleteChar()
    {
        if (eConfig.cy == eConfig.numrows)
            return;

        if (eConfig.cx == 0 && eConfig.cy == 0)
            return;

        RowData* row = &eConfig.row[eConfig.cy];
        if (eConfig.cx > 0) {
            RowDeleteChar(row, eConfig.cx - 1);
            eConfig.cx--;
        } else {
            eConfig.cx = eConfig.row[eConfig.cy - 1].size;
            RowAppendString(&eConfig.row[eConfig.cy - 1], row->chars, row->size);
            DeleteRow(eConfig.cy);
            eConfig.cy--;
        }
    }

    void FreeRow(RowData* row)
    {
        free(row->render);
        free(row->chars);
        free(row->highlight);
    }

    /*---- INPUT ----*/
    void MoveCursor(int key)
    {
        // Prevent cursor from going past the size of the screen not the file
        RowData* row = (eConfig.cy >= eConfig.numrows) ? NULL : &eConfig.row[eConfig.cy];

        switch (key) {
        case ARROW_LEFT:
            if (eConfig.cx != 0) {
                eConfig.cx--;
            } else if (eConfig.cy > 0) {
                eConfig.cy--;
                eConfig.cx = eConfig.row[eConfig.cy].size;
            }

            break;
        case ARROW_RIGHT:
            if (row && eConfig.cx < row->size) {
                eConfig.cx++;
            } else if (row && eConfig.cx == row->size) {
                eConfig.cy++;
                eConfig.cx = 0;
            }

            break;
        case ARROW_UP:
            if (eConfig.cy != 0)
                eConfig.cy--;
            break;
        case ARROW_DOWN:
            if (eConfig.cy < eConfig.numrows)
                eConfig.cy++;
            break;
        }

        // Cursor snap to end of line
        row = (eConfig.cy >= eConfig.numrows) ? NULL : &eConfig.row[eConfig.cy];
        int rowlen = row ? row->size : 0;
        if (eConfig.cx > rowlen)
            eConfig.cx = rowlen;
    }
    
    void ProcessKeypress()
    {
    	static int quit_times = SUSTEXT_QUIT_TIMES;
    	int c = Terminal::editorReadKey();

    	// Bane of my existance
    	switch (c) {
    	case '\r':
    		InsertNewLine();
		break;
	    case CTRL_KEY('q'):
		    if (eConfig.dirty && quit_times > 0) {
	    		SetStatusMessage("File has unsaved changes. "
							"Press Ctrl-Q %d more time(s) to confirm.",
							quit_times);
			    quit_times--;
			    return;
		    }

		    //[2J will erase all of the diaply without moving the cursor position
		    write(STDOUT_FILENO, "\x1b[2J", 4);

		    // Return cursor to home
		    write(STDOUT_FILENO, "\x1b[H", 3);
		    exit(0);
		    break;
	    case CTRL_KEY('s'):
	    	// flags.SetFlags(FILESAVE, true);
	    	return;
	    case HOME_KEY:
	    	eConfig.cx = 0;
	    	break;
	    case END_KEY:
	    	if (eConfig.cx < eConfig.numrows)
	    		eConfig.cx = eConfig.row[eConfig.cy].size;

	    	break;
	    case BACKSPACE:
	    case CTRL_KEY('h'):
	    case DEL_KEY:
	    	if (c == DEL_KEY)
	    		MoveCursor(ARROW_RIGHT);

	    	DeleteChar();
	    	break;
	    case CTRL_KEY('f'):
		    Find();
		    break;
	    case PAGE_UP:
	    case PAGE_DOWN:
		    if (c == PAGE_UP) {
		    	eConfig.cy = eConfig.rowOff;
		    } else if (c == PAGE_DOWN) {
		    	eConfig.cy = eConfig.rowOff + eConfig.screenRows - 1;

		    	if (eConfig.cy > eConfig.numrows)
			    	eConfig.cy = eConfig.numrows;
		    }

		    break;
	    case ARROW_UP:
	    case ARROW_DOWN:
	    case ARROW_LEFT:
	    case ARROW_RIGHT:
		    MoveCursor(c);
		    break;
	    case CTRL_KEY('l'):
	    case '\x1b':
	    	break;
	    default:
	    	InsertChar(c);
	    	break;
	    }

	    quit_times = SUSTEXT_QUIT_TIMES;
    }

    char* RowToString(int* buflen)
    {
        int totalLen = 0;
        for (int i = 0; i < eConfig.numrows; i++) {
            totalLen += eConfig.row[i].size + 1;
        }

        *buflen = totalLen;

        char* buf = (char*)malloc(totalLen);
        char* ptr = buf;

        for (int i = 0; i < eConfig.numrows; i++) {
            memcpy(ptr, eConfig.row[i].chars, eConfig.row[i].size);
            ptr += eConfig.row[i].size;
            *ptr = '\n';
            ptr++;
        }

        fprintf(stderr, "buf out: %s\n", (char *)buf);
        return buf;
    }

    /*---- OUTPUT ----*/
    void Scroll()
    {
        eConfig.rx = 0;
        if (eConfig.cy < eConfig.numrows)
            eConfig.rx = RowCxToRx(&eConfig.row[eConfig.cy], eConfig.cx);

        if (eConfig.cy < eConfig.rowOff)
            eConfig.rowOff = eConfig.cy;

        if (eConfig.cy >= eConfig.rowOff + eConfig.screenRows)
            eConfig.rowOff = eConfig.cy - eConfig.screenRows + 1;

        if (eConfig.rx < eConfig.colOff)
            eConfig.colOff = eConfig.rx;

        if (eConfig.rx >= eConfig.colOff + eConfig.screenCols)
            eConfig.colOff = eConfig.rx - eConfig.screenCols + 1;
    }

    // void DrawRows(struct AppendBuffer::abuf* ab)
    // {
    //     for (int y = 0; y < eConfig.screenRows; y++) {
    //         int filerow = y + eConfig.rowOff;
    //         if (filerow >= eConfig.numrows) {
    //             // Prepare the append buffer
    //             if (eConfig.numrows == 0 && y == eConfig.screenRows / 3) {
    //                 // The welcome text will only show if the editor is opened as a standalone
    //                 // program with no inputs, on file open there is no welcome
    //                 char welcome[80];
    //                 int welcomelen = snprintf(welcome, sizeof(welcome),
    //                                           "sustext editor -- version %s", SUSTEXT_VERSION);
                    
    //                 if (welcomelen > eConfig.screenCols)
    //                     welcomelen = eConfig.screenCols;

    //                 int padding = (eConfig.screenCols - welcomelen) / 2;

    //                 // Padding will always be present on blank lines
    //                 if (padding) {
    //                     abAppend(ab, "~", 1);
    //                     padding--;
    //                 }

    //                 while (padding--) {
    //                     abAppend(ab, " ", 1);
    //                 }

    //                 abAppend(ab, welcome, welcomelen);
    //             } else {
    //                 abAppend(ab, "~", 1);
    //             }
    //         } else {
    //             int len = eConfig.row[filerow].rsize - eConfig.colOff;
    //             // Prevent the length for being a negative number
    //             if (len < 0)
    //                 len = 0;

    //             if (len > eConfig.screenCols)
    //                 len = eConfig.screenCols;

    //             char* c = &eConfig.row[filerow].render[eConfig.colOff];
    //             unsigned char* highlight = &eConfig.row[filerow].highlight[eConfig.colOff];
    //             int currentColor = -1;
    //             for (int j = 0; j < len; j++) {
    //                 if (iscntrl(c[j])) {
    //                     // NULL character check
    //                     char sym = (c[j] <= 26) ? '@' + c[j] : '?';
    //                     AppendBuffer::abAppend(ab, "\x1b[7m", 4);
    //                     AppendBuffer::abAppend(ab, &sym, 1);
    //                     AppendBuffer::abAppend(ab, "\x1b[m", 3);
    //                     if (currentColor != -1) {
    //                         char buf[16];
    //                         int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", currentColor);
    //                         AppendBuffer::abAppend(ab, buf, clen);
    //                     }
    //                 } else if (highlight[j] == HL_NORMAL) {
    //                     if (currentColor == -1) {
    //                         AppendBuffer::abAppend(ab, "\x1b[39m", 5);
    //                         currentColor = -1;
    //                     }

    //                     AppendBuffer::abAppend(ab, &c[j], 1);
    //                 } else {
    //                     int color = SyntaxToColor(highlight[j]);
    //                     if (color != currentColor) {
    //                         currentColor = color;
    //                         char buf[16];
    //                         int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", color);
    //                         AppendBuffer::abAppend(ab, buf, clen);
    //                     }

    //                     AppendBuffer::abAppend(ab, &c[j], 1);
    //                 }
    //             }

    //             AppendBuffer::abAppend(ab, "\x1b[39m", 5);
    //         }

    //         // Since everything for the row is appended to the buffer everything
    //         // after the cursor which effecively produces a clean row
    //         abAppend(ab, "\x1b[K", 3);

    //         // Account for the last row
    //         abAppend(ab, "\r\n", 2);
    //     }
    // }

    // void DrawStatusBar(struct AppendBuffer::abuf* ab)
    // {
    //     AppendBuffer::abAppend(ab, "\x1b[7m", 4);
    //     char status[80], rstatus[80];

    //     int len = snprintf(status, sizeof(status), "%.20s - %d lines %s",
    //                        eConfig.filepath ? eConfig.filepath : "[No Name]", eConfig.numrows,
    //                        eConfig.dirty ? "(modified)" : "");

    //     int rlen = snprintf(rstatus, sizeof(rstatus), "%s | %d/%d",
    //                         eConfig.syntax ? eConfig.syntax->filetype : "no ft", eConfig.cy + 1, eConfig.numrows);
    //     if (len > eConfig.screenCols)
    //         len = eConfig.screenCols;

    //     AppendBuffer::abAppend(ab, status, len);
    //     while (len < eConfig.screenCols) {
    //         if (eConfig.screenCols - len == rlen) {
    //             AppendBuffer::abAppend(ab, rstatus, rlen);
    //             break;
    //         } else {
    //             AppendBuffer::abAppend(ab, " ", 1);
    //             len++;
    //         }
    //     }

    //     AppendBuffer::abAppend(ab, "\x1b[m", 3);
    //     AppendBuffer::abAppend(ab, "\r\n", 2);
    // }

    // void DrawMessageBar(AppendBuffer::abuf* ab)
    // {
    //     AppendBuffer::abAppend(ab, "\x1b[K", 3);
    //     int msglen = strlen(eConfig.statusmsg);
    //     if (msglen > eConfig.screenCols)
    //         msglen = eConfig.screenCols;

    //     if (msglen && time(NULL) - eConfig.statusmsg_time < 5)
    //         AppendBuffer::abAppend(ab, eConfig.statusmsg, msglen);
    // }

    void RefreshScreen()
    {
        // Scroll();
        // struct AppendBuffer::abuf ab = ABUF_INIT;

        // // Use the ?25l esacape sequence to hide to cursor on refresh
        // abAppend(&ab, "\x1b[?25l", 6);
        // abAppend(&ab, "\x1b[H", 3);

        // DrawRows(&ab);
        // DrawStatusBar(&ab);
        // DrawMessageBar(&ab);

        // char buf[32];
        // snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (eConfig.cy - eConfig.rowOff) + 1, (eConfig.rx - eConfig.colOff) + 1);
        // abAppend(&ab, buf, strlen(buf));

        // abAppend(&ab, "\x1b[?25h", 6);

        // write(STDOUT_FILENO, ab.b, ab.len);
        // abFree(&ab);
    }

    void SetStatusMessage(const char* fmt...)
    {
        // va_list ap;
        // va_start(ap, fmt);
        // vsnprintf(eConfig.statusmsg, sizeof(eConfig.statusmsg), fmt, ap);
        // va_end(ap);
        // eConfig.statusmsg_time = time(NULL);
    }

    void UpdateSyntax(RowData* row)
    {
        // row->highlight = (unsigned char*)realloc(row->highlight, row->rsize);
        // memset(row->highlight, HL_NORMAL, row->rsize);

        // if (eConfig.syntax == NULL)
        //     return;

        // char** keywords = eConfig.syntax->keywords;

        // char* scs = eConfig.syntax->singleline_comment_start;
        // char* mcs = eConfig.syntax->multiline_comment_start;
        // char* mce = eConfig.syntax->multiline_comment_end;

        // int scsLen = scs ? strlen(scs) : 0;
        // int mcsLen = mcs ? strlen(mcs) : 0;
        // int mceLen = mce ? strlen(mce) : 0;

        // int prevSep = 1;
        // int inString = 0;
        // int inComment = (row->idx > 0 && eConfig.row[row->idx - 1].hl_open_comment);

        // int i = 0;
        // while (i < row->size) {
        //     char c = row->render[i];
        //     unsigned char prevHL = (i > 0) ? row->highlight[i - 1] : HL_NORMAL;

        //     if (scsLen && !inString && !inComment) {
        //         if (!strncmp(&row->render[i], scs, scsLen)) {
        //             memset(&row->highlight[i], HL_COMMENT, row->rsize - i);
        //             break;
        //         }
        //     }

        //     if (mcsLen && mceLen && !inString) {
        //         if (inComment) {
        //             row->highlight[i] = HL_MLCOMMENT;
        //             if (!strncmp(&row->render[i], mce, mceLen)) {
        //                 memset(&row->highlight[i], HL_MLCOMMENT, mceLen);
        //                 i += mceLen;
        //                 inComment = 0;
        //                 prevSep = 1;
        //                 continue;
        //             } else {
        //                 i++;
        //                 continue;
        //             }
        //         } else if (!strncmp(&row->render[i], mcs, mcsLen)) {
        //             memset(&row->highlight[i], HL_MLCOMMENT, mcsLen);
        //             i += mcsLen;
        //             inComment = 1;
        //             continue;
        //         }
        //     }

        //     if (eConfig.syntax->flags & HL_HIGHLIGHT_STRINGS) {
        //         if (inString) {
        //             row->highlight[i] = HL_STRING;
        //             if (c == '\\' && i + 1 < row->rsize) {
        //                 row->highlight[i + 1] = HL_STRING;
        //                 i += 2;
        //                 continue;
        //             }

        //             if (c == inString)
        //                 inString = 0;

        //             i++;
        //             prevSep = 1;
        //             continue;
        //         } else {
        //             if (c == '"' || c == '\'') {
        //                 inString = c;
        //                 row->highlight[i] = HL_STRING;
        //                 i++;
        //                 continue;
        //             }
        //         }
        //     }

        //     if (eConfig.syntax->flags & HL_HIGHLIGHT_NUMBERS) {
        //         if ((isdigit(c) && prevSep || (prevHL == HL_NUMBER)) || (c == '.' && prevHL == HL_NUMBER)) {
        //             row->highlight[i] = HL_NUMBER;
        //             i++;
        //             prevSep = 0;
        //             continue;
        //         }
        //     }

        //     if (prevSep) {
        //         int j;
        //         for (j = 0; keywords[j]; j++) {
        //             int kLen = strlen(keywords[j]);
        //             int kw2 = keywords[j][kLen - 1] == '|';
        //             if (kw2)
        //                 kLen--;

        //             if (!strncmp(&row->render[i], keywords[j], kLen) && isSeperator(row->render[i + kLen])) {
        //                 memset(&row->highlight[i], kw2 ? HL_KEYWORD_2 : HL_KEYWORD_1, kLen);
        //                 i += kLen;
        //                 break;
        //             }
        //         }

        //         if (keywords[j] != NULL) {
        //             prevSep = 0;
        //             continue;
        //         }
        //     }

        //     prevSep = isSeperator(c);
        //     i++;
        // }

        // int changed = (row->hl_open_comment != inComment);
        // row->hl_open_comment = inComment;

        // if (changed && row->idx + 1 < eConfig.numrows)
        //     UpdateSyntax(&eConfig.row[row->idx + 1]);
    }

    int SyntaxToColor(int highlight)
    {
        // switch (highlight) {
        // case HL_COMMENT:
        // case HL_MLCOMMENT:
        //     return FG_CYAN;
        // case HL_KEYWORD_1:
        //     return FG_YELLOW;
        // case HL_KEYWORD_2:
        //     return FG_GREEN;
        // case HL_STRING:
        //     return FG_MAGENTA;
        // case HL_NUMBER:
        //     return FG_RED;
        // case HL_MATCH:
        //     return FG_BLUE;
        // default:
        //     return FG_WHITE;
        // }
    }

    void SelectSyntaxHighlight()
    {
        // eConfig.syntax = NULL;
        // if (eConfig.filepath == NULL)
        //     return;

        // char* ext = strrchr(eConfig.filepath, '.');

        // for (unsigned int j = 0; j < HLDB_ENTRIES; j++) {
        //     struct EditorSyntax *s = &HLDB[j];
        //     unsigned int i = 0;
        //     while (s->filematch[i]) {
        //         int is_ext = (s->filematch[i][0] == '.');
        //         if ((is_ext && ext && !strcmp(ext, s->filematch[i])) || (!is_ext && strstr(eConfig.filepath, s->filematch[i]))) {
        //             eConfig.syntax = s;

        //             for (int filerow = 0; filerow < eConfig.numrows; filerow++) {
        //                 UpdateSyntax(&eConfig.row[filerow]);
        //             }

        //             return;
        //         }

        //         i++;
        //     }
        // }
    }
}