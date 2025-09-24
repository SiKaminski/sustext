//#pragma GCC diagnostic ignored "-Wswitch"

#include "utils/common.hpp"

#include "editor.hpp"
#include "utils/logger.hpp"
#include "utils/error.h"
#include "keys.h"
#include <bits/stdc++.h>
#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <termios.h>
#include <signal.h>
#include <mutex>

// #include "sustext.h"
// #include "prototypes.h"
// #include "syntaxinfo.hpp"
// #include "filehandler.h"
#include "flaghandler.hpp"

// #include <ctype.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <time.h>
// #include <stdarg.h>

namespace Sustext
{
    namespace Editor
    {
        void Editor::Initialize()
        {
            logger.Log(INFO, "Initializing Editor");

            // Store the current terminal attributes
            mOrigTerm = new termios;
            if(tcgetattr(1, mOrigTerm) != 0)
                logger.Log(ERROR, "tcgetattr");

            // Initialize ncruses functions
            setlocale(LC_ALL, "");
            initscr();
            cbreak();
            keypad(stdscr, TRUE);

            // Disable echo since the user will be in normal mode initially
            noecho();

            mConfig = new EditorConfig;

            // Check for terminal color support
            mConfig->colorSupport = false;
            if (start_color() != ERR)
                mConfig->colorSupport = true;

            // Set general information about the current window
            // config.state |= State::Home;
            mConfig->rows = LINES;
            mConfig->cols = COLS;
            mConfig->mode = NORMAL;

            if (mConfig->filepath == "")
               mConfig->state |= State::WELCOME;
            else
               logger.Log(ERROR, "TODO: Unimplemented file opening");
        }

        EditorConfig* Editor::GetConfig()
        {
            return mConfig;
        }

        void Editor::SetConfig(EditorConfig* newCfg)
        {
            mConfig = newCfg;
        }
        
        termios* Editor::GetOrigTermAttr()
        {
            return this->mOrigTerm;
        }

    //     namespace Editor
    //     {
    //         // Declare misc variables to be used in editor functions
    //         static std::mutex gMutex;
    // 
    //         // Declare callback functions
    //         static void sigwinchHandler(int sig);
    //         static void sigintHandler(int sig);
    // 
    //         void Initialize(int argc, char** argv)
    //         {
    //             if (FlagHandler::Initialize(argc, argv, &config) == FAILURE)
    //                 error(Severity::high, "Flag Handler:", "Unable to initialize flags");
    // 
    //             // Load signal handlers
    //             signal(SIGWINCH, sigwinchHandler);
    //             signal(SIGINT, sigintHandler);
    // 
    //             //tConfig.state = Terminal::State::home;
    // 
    //             //if (Terminal::GetWindowSize(&eConfig.screenRows, &eConfig.screenCols) == -1) 
    //             //Terminal::die((int)Severity::medium, "getWindowSize");
    // 
    //             //Account for status bar sapce so it won't be drawn over
    //             //eConfig.screenRows -= 2; 
    // 
    //             config.running = true;
    //             logger.Log(SUCCESS, "Initialized Editor");
    //         }
    // 
    //         void WelcomeScreen()
    //         {
    //             logger.Log(DEBUG, "Preparing Welcome Screen");
    // 
    //             char welcome[80];
    //             int welcomelen = snprintf(welcome, sizeof(welcome), "sustext editor -- version %s", VERSION);
    //             int padding = (config.cols - welcomelen) / 2;
    //             
    //             if (welcomelen > config.cols)
    //                 welcomelen = config.cols;
    // 
    //             config.windows.GrettingText = newwin(4, welcomelen, config.rows / 2, padding);
    //             waddstr(config.windows.GrettingText, welcome);
    //             wrefresh(config.windows.GrettingText);
    //             logger.Log(DEBUG, "Welcome Screen prepared"); 
    //         }
    // 
    //         size_t DumpState(std::string filepath)
    //         {
    //             std::ofstream logFile;
    //             logFile.open(filepath);
    // 
    //             logFile << "\n---------- DUMPING CURRENT STATE ----------\n";
    //             logFile << "Raw: " << config.state << "\n";
    //             logFile << "Raw Binary: " << std::bitset<64>(config.state) << "\n"; 
    //             logFile << "-------------------------------------------\n";
    //             logFile.close();
    // 
    //             return config.state;
    //         }
    // 
    //         // Callbacks
    //         void sigwinchHandler(int sig)
    //         {
    //             gMutex.lock();
    //             {
    //                 winsize tmpWinsize;
    //            
    //             // Disable echo since the user will be in normal mode initially
    //                 if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &tmpWinsize) < 0)
    //                     error(Severity::high, "sigwinchHandler:", "Error getting new size for window");
    // 
    //                 config.rows = tmpWinsize.ws_row;
    //                 config.cols = tmpWinsize.ws_col;
    //             }
    //             gMutex.unlock();
    //         }
    // 
    //         void sigintHandler(int sig)
    //         {
    //             // TODO: Properly dispose of everything
    //             if (config.mode == Mode::Insert)
    //                 return;
    // 
    //             endwin();
    //             exit(0);
    //         }
    // 
    //         void ProcessKeypress()
    //         {
    //             int pressed = getch();
    // 
    //             if (pressed == esc) {
    //                 EnterNormalMode();
    //                 return;
    //             }
    //             
    //             if (config.mode == Mode::Normal)
    //                 NormalKeyHandler(pressed);
    //             else if (config.mode == Mode::Insert)
    //                 InsertKeyHandler(pressed);
    //             else if (config.mode == Mode::Visual)
    //                 VisualKeyHandler(pressed);
    //         }
    // 
    //         void NormalKeyHandler(int key)
    //         {
    //             switch (key) {
    //                 case 'i':
    //                 {
    //                     logger.Log(DEBUG, "Entering Insert mode"); 
    //                     EnterInsertMode();
    //                     break;
    //                 }
    //                 case 'v':
    //                 {
    //                     logger.Log(DEBUG, "Entering Visual mode"); 
    //                     EnterVisualMode();
    //                     break;
    //                 }
    //                 case KEY_LEFT:
    //                 case 'h':
    //                 {
    //                     config.cursorPos.x--;
    //                     MoveCursor(config.cursorPos);
    //                     break;
    //                 }
    //                 case KEY_DOWN:
    //                 case 'j':
    //                 {
    //                     config.cursorPos.y++;
    //                     MoveCursor(config.cursorPos);
    //                     break;
    //                 }
    //                 case KEY_UP:
    //                 case 'k':
    //                 {
    //                     config.cursorPos.y--;
    //                     MoveCursor(config.cursorPos);
    //                     break;
    //                 }
    //                 case KEY_RIGHT:
    //                 case 'l':
    //                 {
    //                     config.cursorPos.x++;
    //                     MoveCursor(config.cursorPos);
    //                     break;
    //                 }
    //                 case ':':
    //                 {
    //                     nocbreak();
    //                     char cmd[100];
    //                     getstr(cmd);
    //                     NormalCommandHandler(cmd);
    //                     cbreak();
    //                     break;
    //                 }
    //                 default:
    //                 {
    //                     logger.Log(DEBUG, "Unimplemented Normal mode key [%d]", key);
    //                     break;
    //                 }
    //             }
    //         }
    // 
    //         void NormalCommandHandler(char* cmd)
    //         {
    //             std::string cmdStr = cmd;
    //             if (cmdStr == "q")
    //                 sigintHandler(SIGINT);
    //         }
    // 
    //         void InsertKeyHandler(int key)
    //         {
    //             switch (key) {
    //                 default:
    //                 {
    //                     printw("%c", key);
    //                     break;
    //                 }
    //             }
    //         }
    //         
    //         void VisualKeyHandler(int key)
    //         {
    //             switch (key) {
    //                 default:
    //                 {
    //                     logger.Log(DEBUG, "Unimplemented Normal mode key [%d]", key);
    //                     break;
    //                 }
    //             }
    //         }
    // 
    //         void MoveCursor(Position pos)
    //         {
    //             if (pos.x >= config.cols)
    //                 pos.x = config.cols;
    //             else if (pos.x <= 0)
    //                 pos.x = 0;
    // 
    //             if (pos.y >= config.rows)
    //                 pos.y = config.rows;
    //             else if (pos.y <= 0)
    //                 pos.y = 0;
    // 
    //             move(pos.y, pos.x);
    //         // Prevent cursor from going past the size of the screen not the file
    //         //RowData* row = (eConfig.cy >= eConfig.numrows) ? nullptr : &eConfig.row[eConfig.cy];
    // 
    //         //switch (key) {
    //         //case Key::arrowLeft:
    //         //{
    //         //if (eConfig.cx != 0) {
    //         //eConfig.cx--;
    //         //} else if (eConfig.cy > 0) {
    //         //eConfig.cy--;
    //         //eConfig.cx = eConfig.row[eConfig.cy].size;
    //         //}
    // 
    //         //break;
    //         //}
    //         //case Key::arrowRight:
    //         //{
    //         //if (row && eConfig.cx < row->size) {
    //         //eConfig.cx++;
    //         //} else if (row && eConfig.cx == row->size) {
    //         //eConfig.cy++;
    //         //eConfig.cx = 0;
    //         //}
    // 
    //         //break;
    //         //}
    //         //case Key::arrowUp:
    //         //{
    //         //if (eConfig.cy != 0)
    //         //eConfig.cy--;
    //         //break;
    //         //}
    //         //case Key::arrowDown:
    //         //{
    //         //if (eConfig.cy < eConfig.numrows)
    //         //eConfig.cy++;
    //         //break;
    //         //}
    //         //}
    // 
    //         // Cursor snap to end of line
    //         //row = (eConfig.cy >= eConfig.numrows) ? nullptr : &eConfig.row[eConfig.cy];
    //         //int rowlen = row ? row->size : 0;
    //         //if (eConfig.cx > rowlen)
    //         //eConfig.cx = rowlen;
    //         }
    //             //static int quit_times = Sustext::QUIT_TIMES;
    //             //Key key = Terminal::EditorReadKey();
    // 
    //             //switch (key) {
    //                 //case Key::carriageRet:
    //                 //{
    //                     //InsertNewLine();
    //                     //break;
    //                 //}
    //                 //case Key::ctrl_q:
    //                 //{
    //                     //if (eConfig.dirty && quit_times > 0) {
    //                         //SetStatusMessage("File has unsaved changes. "
    //                                     //"Press Ctrl-Q %d more time(s) to confirm.",
    //                                     //quit_times);
    //                         //quit_times--;
    //                         //return;
    //                     //}
    // 
    //                     //[2J will erase all of the diaply without moving the cursor position
    //                     //write(STDOUT_FILENO, "\x1b[2J", 4);
    // 
    //                     // Return cursor to home
    //                     //write(STDOUT_FILENO, "\x1b[H", 3);
    //                     //exit(0);
    //                     //break;
    //                 //}
    //                 //case Key::ctrl_s:
    //                 //{
    //                     //FileHandler::SaveFile();
    //                     //return;
    //                 //}
    //                 //case Key::home:
    //                 //{
    //                     //eConfig.cx = 0;
    //                     //break;
    //                 //}
    //                 //case Key::end:
    //                 //{
    //                     //if (eConfig.cx < eConfig.numrows)
    //                         //eConfig.cx = eConfig.row[eConfig.cy].size;
    // 
    //                     //break;
    //                 //}
    //                 //case Key::backspace:
    //                 //case Key::ctrl_h:
    //                 //case Key::del:
    //                 //{
    //                     //if (key == Key::del)
    //                         //MoveCursor(Key::arrowRight);
    //                     
    //                     //DeleteChar();
    //                     //break;
    //                 //}
    //                 //case Key::ctrl_f:
    //                 //{
    //                     //Find();
    //                     //break;
    //                 //}
    //                 //case Key::pageUp:
    //                 //case Key::pageDown:
    //                 //{
    //                     //if (key == Key::pageUp) {
    //                         //eConfig.cy = eConfig.rowOff;
    //                     //} else if (key == Key::pageDown) {
    //                         //eConfig.cy = eConfig.rowOff + eConfig.screenRows - 1;
    // 
    //                         //if (eConfig.cy > eConfig.numrows)
    //                             //eConfig.cy = eConfig.numrows;
    //                     //}
    // 
    //                     //break;
    //                 //}
    //                 //case Key::arrowUp:
    //                 //case Key::arrowDown:
    //                 //case Key::arrowLeft:
    //                 //case Key::arrowRight:
    //                 //{
    //                     //MoveCursor(key);
    //                     //break;
    //                 //}
    //                 //case Key::ctrl_l:
    //                 //case Key::escapeSequence:
    //                 //{
    //                     //break;
    //                 //}
    //                 //default:
    //                 //{
    //                     //InsertChar((int)key);
    //                     //break;
    //                 //}
    //             //}
    // 
    //             //quit_times = Sustext::QUIT_TIMES;
    // 
    //         void RefreshScreen()
    //         {
    //             if ((State::Welcome & config.state) > 0)
    //                 WelcomeScreen();
    // 
    //             refresh();
    //             //Scroll();
    //             //AppendBuffer::abuf ab = {};
    // 
    //             // Use the ?25l esacape sequence to hide to cursor on refresh
    //             //abAppend(&ab, "\x1b[?25l", 6);
    //             //abAppend(&ab, "\x1b[H", 3);
    // 
    //             //DrawRows(&ab);
    //             //DrawStatusBar(&ab);
    //             //DrawMessageBar(&ab);
    // 
    //             //char buf[32];
    //             //snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (eConfig.cy - eConfig.rowOff) + 1, (eConfig.rx - eConfig.colOff) + 1);
    //             //abAppend(&ab, buf, strlen(buf));
    // 
    //             //abAppend(&ab, "\x1b[?25h", 6);
    // 
    //             //write(STDOUT_FILENO, ab.b, ab.len);
    //             //abFree(&ab);
    //             
    //             // Call ncurses refresh
    //         }
    // 
    //         void EnterInsertMode()
    //         {
    //             config.mode = Mode::Insert;
    //             raw();
    //         }
    // 
    //         void EnterNormalMode()
    //         {
    //             config.mode = Mode::Normal;
    //             
    //             cbreak();
    //             keypad(stdscr, TRUE);
    //             noecho();
    //         }
    // 
    //         void EnterVisualMode()
    //         {
    //             config.mode = Mode::Visual;
    //         }
    // 
    //         // ---- ROW OPERATIONS ----
    // 
    //         void DrawPrompt(std::string prompt, void(*callback)(char*, int, Config))
    //         {
    //         //size_t bufsize = 128;
    //         //char* buf = new char[bufsize];
    // 
    //         //size_t buflen = 0;
    //         //buf[0] = '\0';
    // 
    //         //while (true) {
    //         //SetStatusMessage(prompt, buf);
    //         //RefreshScreen();
    //         //int padding = 0;
    // 
    //         //Key key = Terminal::EditorReadKey();
    // 
    //         // Check if user is removing a character
    //         //if (key == Key::del || key == (Key)CTRL_KEY('h') || key == Key::backspace) {
    //         //if (buflen != 0)
    //         //buf[--buflen] = '\0';
    //         //} else if (key == Key::escapeSequence) {
    //         //SetStatusMessage("");
    //         //if (callback)
    //         //callback(buf, key, &eConfig);
    // 
    //         //free(buf);
    //         //return nullptr;
    //         //} else if (key == Key::carriageRet) {
    //         //if (buflen != 0) {
    //         //SetStatusMessage("");
    //         //if (callback)
    //         //callback(buf, key, &eConfig);
    // 
    //         //return buf;
    //         //}
    //         //} else if (!iscntrl((int)key) && (int)key < 128) {
    //         //if (buflen == bufsize - 1) {
    //         //bufsize *= 2;
    //         //buf = (char*)realloc(buf, bufsize);
    //         //}
    // 
    //         //buf[buflen++] = (char)key;
    //         //buf[buflen] = '\0';
    //         //}
    // 
    //         //if (callback)
    //         //callback(buf, key, &eConfig);
    //         //}
    //         //}
    // 
    //         //void Find()
    //         //{
    //         //int savedCx = eConfig.cx;
    //         //int savedCy = eConfig.cy;
    //         //int savedColOff = eConfig.colOff;
    //         //int savedRowOff = eConfig.rowOff;
    // 
    //         // Set up query prompt position to the bottom of the screen
    //         //char* query = Prompt("Search -> %s (ESC to cancel)", FindCallBack);
    // 
    //         //if (query) {
    //         //free(query);
    //         //} else {
    //         //eConfig.cx = savedCx;
    //         //eConfig.cy = savedCy;
    //         //eConfig.colOff = savedColOff;
    //         //eConfig.rowOff = savedRowOff;
    //         //}
    //         }
    // 
    //         //void UpdateRow(RowData* row) 
    //         //{
    //         //int tabs = 0;
    //         //for (int j = 0; j < row->size; j++) {
    //         //if (row->chars[j] == '\t')
    //         //tabs++;
    //         //}
    // 
    //         //// Free what was in the row previously and update it
    //         //free(row->render);
    //         //row->render = new char[row->size + tabs * (Sustext::TAB_STOP - 1) + 1];
    // 
    //         //// Update each character in the row
    //         //int i = 0;
    //         //for (int j = 0; j < row->size; j++) {
    //         //if (row->chars[j] == '\t') {
    //         //row->render[i++] = ' ';
    //         //while (i % Sustext::TAB_STOP != 0) {
    //         //row->render[i++] = ' ';
    //         //}
    //         //} else {
    //         //row->render[i++] = row->chars[j];
    //         //}
    //         //}
    // 
    //         //row->render[i] = '\0';
    //         //row->rsize = i;
    //         //UpdateSyntax(row);
    //         //}
    // 
    //         //void InsertRow(int pos, char* s, size_t len)
    //         //{
    //         //if (pos < 0 || pos > eConfig.numrows)
    //         //return;
    // 
    //         //eConfig.row = static_cast<RowData*>(realloc(eConfig.row, sizeof(RowData) * (eConfig.numrows + 1)));
    //         //memmove(&eConfig.row[pos + 1], &eConfig.row[pos], sizeof(RowData) * (eConfig.numrows - pos));
    //         //for (int i = pos + 1; i <= eConfig.numrows; i++) {
    //         //eConfig.row[i].idx++;
    //         //}
    // 
    //         //eConfig.row[pos].idx = pos;
    //         //eConfig.row[pos].size = len;
    //         //eConfig.row[pos].chars = new char[len + 1];
    // 
    //         //memcpy(eConfig.row[pos].chars, s, len);
    //         //eConfig.row[pos].chars[len] = '\0';
    // 
    //         //// Initialize render for buffer
    //         //eConfig.row[pos].rsize = 0;
    //         //eConfig.row[pos].render = nullptr;
    //         //eConfig.row[pos].highlight = nullptr;
    //         //eConfig.row[pos].hl_open_comment = 0;
    //         //UpdateRow(&eConfig.row[pos]);
    // 
    //         //eConfig.numrows++;
    //         //eConfig.dirty++;
    //         //}
    // 
    //         //void RowInsertChar(RowData* row, int pos, int c)
    //         //{
    //         //if (pos < 0 || pos > row->size)
    //         //pos = row->size;
    // 
    //         //row->chars = static_cast<char*>(realloc(row->chars, row->size + 2));
    //         //memmove(&row->chars[pos + 1], &row->chars[pos], row->size - pos + 1);
    //         //row->size++;
    //         //row->chars[pos] = c;
    //         //UpdateRow(row);
    //         //eConfig.dirty++;
    //         //}
    // 
    //         //void InsertChar(int c)
    //         //{
    //         //if (eConfig.cy == eConfig.numrows)
    //         //InsertRow(eConfig.numrows, (char*)"", 0);
    // 
    //         //RowInsertChar(&eConfig.row[eConfig.cy], eConfig.cx, c);
    //         //eConfig.cx++;
    //         //}
    // 
    //         //void InsertNewLine()
    //         //{
    //         //if (eConfig.cx == 0) {
    //         //InsertRow(eConfig.cy, (char*)"", 0);
    //         //} else {
    //         //RowData* row = &eConfig.row[eConfig.cy];
    //         //InsertRow(eConfig.cy + 1, &row->chars[eConfig.cx], row->size - eConfig.cx);
    //         //row = &eConfig.row[eConfig.cy];
    //         //row->size = eConfig.cx;
    //         //row->chars[row->size] = '\0';
    //         //UpdateRow(row);
    //         //}
    // 
    //         //eConfig.cy++;
    //         //eConfig.cx = 0;
    //         //}
    // 
    //         //void RowAppendString(RowData* row, char* str, size_t len)
    //         //{
    //         //row->chars = static_cast<char*>(realloc(row->chars, sizeof(char) * (row->size + len + 1)));
    //         //memcpy(&row->chars[row->size], str, len);
    //         //row->size += len;
    //         //row->chars[row->size] = '\0';
    //         //UpdateRow(row);
    //         //eConfig.dirty++;
    //         //}
    // 
    //         //void DeleteRow(int pos)
    //         //{
    //         //if (pos < 0 || pos >= eConfig.numrows)
    //         //return;
    // 
    //         //FreeRow(&eConfig.row[pos]);
    //         //memmove(&eConfig.row[pos], &eConfig.row[pos + 1], sizeof(RowData) * (eConfig.numrows - pos - 1));
    //         //for (int i = pos; eConfig.numrows - i ; i++) {
    //         //eConfig.row[i].idx--;
    //         //}
    // 
    //         //eConfig.numrows--;
    //         //eConfig.dirty++;
    //         //}
    // 
    //         //void RowDeleteChar(RowData* row, int pos)
    //         //{
    //         //if (pos < 0 || pos >= row->size)
    //         //return;
    // 
    //         //memmove(&row->chars[pos], &row->chars[pos + 1], row->size - pos);
    //         //row->size--;
    //         //UpdateRow(row);
    //         //eConfig.dirty++;
    //         //}
    // 
    //         //void DeleteChar()
    //         //{
    //         //if (eConfig.cy == eConfig.numrows)
    //         //return;
    // 
    //         //if (eConfig.cx == 0 && eConfig.cy == 0)
    //         //return;
    // 
    //         //RowData* row = &eConfig.row[eConfig.cy];
    //         //if (eConfig.cx > 0) {
    //         //RowDeleteChar(row, eConfig.cx - 1);
    //         //eConfig.cx--;
    //         //} else if (eConfig.cx == 0) {
    //         // DeleteRow(eConfig.cy);
    //         //RowAppendString(&eConfig.row[eConfig.cy - 1], row->chars, row->size);
    //         //eConfig.cx = eConfig.row[eConfig.cy - 1].size - row->size;
    //         //DeleteRow(eConfig.cy);
    //         //eConfig.cy = eConfig.cy == 0 ? 0 : eConfig.cy - 1;
    //         // eConfig.cx = eConfig.row[eConfig.cy - 1].size;
    //         //} else {
    //         //eConfig.cx = eConfig.row[eConfig.cy - 1].size;
    //         //RowAppendString(&eConfig.row[eConfig.cy - 1], row->chars, row->size);
    //         //DeleteRow(eConfig.cy);
    //         //eConfig.cy--;
    //         //}
    //         //}
    // 
    //         //void FreeRow(RowData* row)
    //         //{
    //         //free(row->render);
    //         //free(row->chars);
    //         //free(row->highlight);
    //         //}
    // 
    //         // ---- INPUT ----
    // 
    //         //char* RowToString(int* buflen)
    //         //{
    //             //int totalLen = 0;
    //             //for (int i = 0; i < eConfig.numrows; i++) {
    //                 //totalLen += eConfig.row[i].size + 1;
    //             //}
    // 
    //             //*buflen = totalLen;
    // 
    //             //char* buf = new char[totalLen];
    //             //char* ptr = buf;
    // 
    //             //for (int i = 0; i < eConfig.numrows; i++) {
    //                 //memcpy(ptr, eConfig.row[i].chars, eConfig.row[i].size);
    //                 //ptr += eConfig.row[i].size;
    //                 //*ptr = '\n';
    //                 //ptr++;
    //             //}
    // 
    //             //fprintf(stderr, "buf out: %s\n", static_cast<char*>(buf));
    //             //return buf;
    //         //}
    // 
    //         // ---- OUTPUT ----
    //         //void Scroll()
    //         //{
    //             //eConfig.rx = 0;
    //             //if (eConfig.cy < eConfig.numrows)
    //                 //eConfig.rx = RowCxToRx(&eConfig.row[eConfig.cy], eConfig.cx);
    // 
    //             //if (eConfig.cy < eConfig.rowOff)
    //                 //eConfig.rowOff = eConfig.cy;
    // 
    //             //if (eConfig.cy >= eConfig.rowOff + eConfig.screenRows)
    //                 //eConfig.rowOff = eConfig.cy - eConfig.screenRows + 1;
    // 
    //             //if (eConfig.rx < eConfig.colOff)
    //                 //eConfig.colOff = eConfig.rx;
    // 
    //             //if (eConfig.rx >= eConfig.colOff + eConfig.screenCols)
    //                 //eConfig.colOff = eConfig.rx - eConfig.screenCols + 1;
    //         //}
    // 
    //         //void DrawRows(AppendBuffer::abuf* ab)
    //         //{
    //             //for (int y = 0; y < eConfig.screenRows; y++) {
    //                 //int filerow = y + eConfig.rowOff;
    //                 //if (filerow >= eConfig.numrows) {
    //                     // Prepare the append buffer
    //                     //if (eConfig.numrows == 0 && y == eConfig.screenRows / 3) {
    //                         // The welcome text will only show if the editor is opened as a standalone
    //                         // program with no inputs, on file open there is no welcome
    //                         //char welcome[80];
    //                         //int welcomelen = snprintf(welcome, sizeof(welcome),
    //                                                   //"sustext editor -- version %s", Sustext::VERSION);
    //                         
    //                         //if (welcomelen > eConfig.screenCols)
    //                             //welcomelen = eConfig.screenCols;
    // 
    //                         //int padding = (eConfig.screenCols - welcomelen) / 2;
    // 
    //                         // Padding will always be present on blank lines
    //                         //if (padding) {
    //                             //abAppend(ab, "~", 1);
    //                             //padding--;
    //                         //}
    // 
    //                         //while (padding--) {
    //                             //abAppend(ab, " ", 1);
    //                         //}
    // 
    //                         //abAppend(ab, welcome, welcomelen);
    //                     //} else {
    //                         //abAppend(ab, "~", 1);
    //                     //}
    //                 //} else {
    //                     //int len = eConfig.row[filerow].rsize - eConfig.colOff;
    //                     
    //                     // Prevent the length for being a neg:ative number
    //                     //len = (len < 0) ? 0 : len;
    // 
    //                     //if (len > eConfig.screenCols)
    //                         //len = eConfig.screenCols;
    // 
    //                     //char* c = &eConfig.row[filerow].render[eConfig.colOff];
    //                     //byte* highlight = &eConfig.row[filerow].highlight[eConfig.colOff];
    //                     //int currentColor = -1;
    //                     //for (int j = 0; j < len; j++) {
    //                         //if (iscntrl(c[j])) {
    //                             // nullptr character check
    //                             //char sym = (c[j] <= 26) ? '@' + c[j] : '?';
    //                             //AppendBuffer::abAppend(ab, "\x1b[7m", 4);
    //                             //AppendBuffer::abAppend(ab, &sym, 1);
    //                             //AppendBuffer::abAppend(ab, "\x1b[m", 3);
    //                             
    //                             //if (currentColor != -1) {
    //                                 //char buf[16];
    //                                 //int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", currentColor);
    //                                 //AppendBuffer::abAppend(ab, buf, clen);
    //                             //}
    //                         //} else if (highlight[j] == (byte)Highlight::normal) {
    //                             //if (currentColor == -1)
    //                                 //AppendBuffer::abAppend(ab, "\x1b[39m", 5);
    // 
    //                             //AppendBuffer::abAppend(ab, &c[j], 1);
    //                         //} else {
    //                             //Foreground color = SyntaxToColor((Highlight)highlight[j]);
    //                             //if ((int)color != currentColor) {
    //                                 //currentColor = (int)color;
    //                                 //char buf[16];
    //                                 //int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", (int)color);
    //                                 //AppendBuffer::abAppend(ab, buf, clen);
    //                             //}
    // 
    //                             //AppendBuffer::abAppend(ab, &c[j], 1);
    //                         //}
    //                     //}
    // 
    //                     //AppendBuffer::abAppend(ab, "\x1b[39m", 5);
    //                 //}
    // 
    //                 // Since everything for the row is appended to the buffer everything
    //                 // after the cursor which effecively produces a clean row
    //                 //abAppend(ab, "\x1b[K", 3);
    // 
    //                 // Account for the last row
    //                 //abAppend(ab, "\r\n", 2);
    //             //}
    //         //}
    // 
    //         //void DrawStatusBar(AppendBuffer::abuf* ab)
    //         //{
    //             //AppendBuffer::abAppend(ab, "\x1b[7m", 4);
    //             //char status[80];
    //             //char rstatus[80];
    // 
    //             //int len = snprintf(status, sizeof(status), "%.20s - %d lines %s",
    //                                //eConfig.filepath ? eConfig.filepath : "[No Name]", eConfig.numrows,
    //                                //eConfig.dirty ? "(modified)" : "");
    // 
    //             //int rlen = snprintf(rstatus, sizeof(rstatus), "%s | %d/%d",
    //                                 //eConfig.syntax ? eConfig.syntax->filetype : "no ft", eConfig.cy + 1, eConfig.numrows);
    //             //if (len > eConfig.screenCols)
    //                 //len = eConfig.screenCols;
    // 
    //             //AppendBuffer::abAppend(ab, status, len);
    //             //while (len < eConfig.screenCols) {
    //                 //if (eConfig.screenCols - len == rlen) {
    //                     //AppendBuffer::abAppend(ab, rstatus, rlen);
    //                     //break;
    //                 //} else {
    //                     //AppendBuffer::abAppend(ab, " ", 1);
    //                     //len++;
    //                 //}
    //             //}
    // 
    //             //AppendBuffer::abAppend(ab, "\x1b[m", 3);
    //             //AppendBuffer::abAppend(ab, "\r\n", 2);
    //         //}
    // 
    //         //void DrawMessageBar(AppendBuffer::abuf* ab)
    //         //{
    //             //AppendBuffer::abAppend(ab, "\x1b[K", 3);
    //             //int msglen = strlen(eConfig.statusmsg);
    //             //if (msglen > eConfig.screenCols)
    //                 //msglen = eConfig.screenCols;
    // 
    //             //if (msglen && time(nullptr) - eConfig.statusmsg_time < 5)
    //                 //AppendBuffer::abAppend(ab, eConfig.statusmsg, msglen);
    //         //}
    // 
    //         //void SetStatusMessage(const char* fmt...)
    //         //{
    //             //va_list ap;
    //             //va_start(ap, fmt);
    //             //vsnprintf(eConfig.statusmsg, sizeof(eConfig.statusmsg), fmt, ap);
    //             //va_end(ap);
    //             //eConfig.statusmsg_time = time(nullptr);
    //         //}
    // 
    //         //void UpdateSyntax(RowData* row)
    //         //{
    //             //row->highlight = static_cast<byte*>(realloc(row->highlight, sizeof(byte) * row->rsize));
    //             //memset(row->highlight, (int)Highlight::normal, row->rsize);
    // 
    //             //if (eConfig.syntax == nullptr)
    //                 //return;
    // 
    //             //char** keywords = eConfig.syntax->keywords;
    // 
    //             //char* scs = eConfig.syntax->singleline_comment_start;
    //             //char* mcs = eConfig.syntax->multiline_comment_start;
    //             //char* mce = eConfig.syntax->multiline_comment_end;
    // 
    //             //int scsLen = scs ? strlen(scs) : 0;
    //             //int mcsLen = mcs ? strlen(mcs) : 0;
    //             //int mceLen = mce ? strlen(mce) : 0;
    // 
    //             //int prevSep = 1;
    //             //int inString = 0;
    //             //int inComment = (row->idx > 0 && eConfig.row[row->idx - 1].hl_open_comment);
    // 
    //             //for(int i = 0; i < row->size; i++) {
    //                 //char c = row->render[i];
    //                 //byte prevHL = (i > 0) ? row->highlight[i - 1] : (byte)Highlight::normal;
    // 
    //                 //if (scsLen && !inString && !inComment) {
    //                     //if (!strncmp(&row->render[i], scs, scsLen)) {
    //                         //memset(&row->highlight[i], (int)Highlight::comment, row->rsize - i);
    //                         //break;
    //                     //}
    //                 //}
    // 
    //                 //if (mcsLen && mceLen && !inString) {
    //                     //if (inComment) {
    //                         //row->highlight[i] = (byte)Highlight::mlComment;
    //                         //if (!strncmp(&row->render[i], mce, mceLen)) {
    //                             //memset(&row->highlight[i], (int)Highlight::mlComment, mceLen);
    //                             //i += mceLen;
    //                             //inComment = 0;
    //                             //prevSep = 1;
    //                             //continue;
    //                         //} else {
    //                             //i++;
    //                             //continue;
    //                         //}
    //                     //} else if (!strncmp(&row->render[i], mcs, mcsLen)) {
    //                         //memset(&row->highlight[i], (int)Highlight::mlComment, mcsLen);
    //                         //i += mcsLen;
    //                         //inComment = 1;
    //                         //continue;
    //                     //}
    //                 //}
    // 
    //                 //if (eConfig.syntax->flags & HL_HIGHLIGHT_STRINGS) {
    //                     //if (inString) {
    //                         //row->highlight[i] = (byte)Highlight::string;
    //                         //if (c == '\\' && i + 1 < row->rsize) {
    //                             //row->highlight[i + 1] = (byte)Highlight::string;
    //                             //i += 2;
    //                             //continue;
    //                         //}
    // 
    //                         //if (c == inString)
    //                             //inString = 0;
    // 
    //                         //i++;
    //                         //prevSep = 1;
    //                         //continue;
    //                     //} else {
    //                         //if (c == '"' || c == '\'') {
    //                             //inString = c;
    //                             //row->highlight[i] = (byte)Highlight::string;
    //                             //i++;
    //                             //continue;
    //                         //}
    //                     //}
    //                 //}
    // 
    //                 //if (eConfig.syntax->flags & HL_HIGHLIGHT_NUMBERS) {
    //                     //if (((isdigit(c) && prevSep) || (prevHL == (byte)Highlight::number)) || (c == '.' && prevHL == (byte)Highlight::number)) {
    //                         //row->highlight[i] = (byte)Highlight::number;
    //                         //i++;
    //                         //prevSep = 0;
    //                         //continue;
    //                     //}
    //                 //}
    // 
    //                 //if (prevSep) {
    //                     //int j;
    //                     //for (j = 0; keywords[j]; j++) {
    //                         //int kLen = strlen(keywords[j]);
    //                         //int kw2 = keywords[j][kLen - 1] == '|';
    //                         //if (kw2)
    //                             //kLen--;
    // 
    //                         //if (!strncmp(&row->render[i], keywords[j], kLen) && isSeperator(row->render[i + kLen])) {
    //                             //memset(&row->highlight[i], kw2 ? (int)Highlight::keyword2 : (int)Highlight::keyword1, kLen);
    //                             //i += kLen;
    //                             //break;
    //                         //}
    //                     //}
    // 
    //                     //if (keywords[j] != nullptr) {
    //                         //prevSep = 0;
    //                         //continue;
    //                     //}
    //                 //}
    // 
    //                 //prevSep = isSeperator(c);
    //             //}
    // 
    //             //int changed = (row->hl_open_comment != inComment);
    //             //row->hl_open_comment = inComment;
    // 
    //             //if (changed && row->idx + 1 < eConfig.numrows)
    //                 //UpdateSyntax(&eConfig.row[row->idx + 1]);
    //         //}
    // 
    //         //Foreground SyntaxToColor(Highlight highlight)
    //         //{
    //             //switch (highlight) {
    //                 //case Highlight::comment:
    //                 //case Highlight::mlComment:
    //                     //return Foreground::cyan;
    //                 //case Highlight::keyword1:
    //                     //return Foreground::yellow;
    //                 //case Highlight::keyword2:
    //                     //return Foreground::green;
    //                 //case Highlight::string:
    //                     //return Foreground::magenta;
    //                 //case Highlight::number:
    //                     //return Foreground::red;
    //                 //case Highlight::match:
    //                     //return Foreground::blue;
    //                 //default:
    //                     //return Foreground::white;
    //             //}
    //         //}
    // 
    //         //void SelectSyntaxHighlight()
    //         //{
    //             //eConfig.syntax = nullptr;
    //             //if (eConfig.filepath == nullptr)
    //                 //return;
    // 
    //             //char* ext = strrchr(eConfig.filepath, '.');
    // 
    //             //for (unsigned int j = 0; j < HLDB_ENTRIES; j++) {
    //                 //Syntax *s = &HLDB[j];
    //                 //for(unsigned int i = 0; s->filematch[i]; i++) {
    //                     //int is_ext = (s->filematch[i][0] == '.');
    //                     //if ((is_ext && ext && !strcmp(ext, s->filematch[i])) || (!is_ext && strstr(eConfig.filepath, s->filematch[i]))) {
    //                         //eConfig.syntax = s;
    // 
    //                         //for (int filerow = 0; filerow < eConfig.numrows; filerow++) {
    //                             //UpdateSyntax(&eConfig.row[filerow]);
    //                         //}
    // 
    //                         //return;
    //                     //}
    //                 //}
    //             //}
    //         //}
    //     //}
    // 
    //     //int RowCxToRx(Editor::RowData* row, int cx)
    //     //{
    //         //int rx = 0;
    //         //for (int i = 0; i < cx; i++) {
    //             // Check to see how many columns to the left of the next tab the cursor is
    //             //if (row->chars[i] == '\t')
    //                 //rx += (Sustext::TAB_STOP - 1) - (rx % Sustext::TAB_STOP);
    // 
    //             //rx++;
    //         //}
    // 
    //         //return rx;
    //     //}
    // 
    //     //int RowRxToCx(Editor::RowData* row, int rx)
    //     //{
    //         //int curRx = 0;
    //         //int cx;
    //         //for (cx = 0; cx < row->size; cx++) {
    //             //if (row->chars[cx] == '\t')
    //                 //curRx += (Sustext::TAB_STOP - 1) - (curRx % Sustext::TAB_STOP);
    // 
    //             //curRx++;
    //             //if (curRx > rx)
    //                 //return cx;
    //         //}
    // 
    //         //return cx;
    //     //}
    // 
    //     //int isSeperator(int c)
    //     //{
    //         //return isspace(c) || c == '\0' || strchr(",.()+-/*=~%<>[];", c) != nullptr;
    //     //}
    // 
    //     //void FindCallBack(char* query, Editor::Key key, Editor::Config* E)
    //     //{
    //         //using namespace Editor;
    // 
    //         //static int lastMatch = -1;
    //         //static int direction = 1;
    //         //static int savedHighlightLine;
    //         //static char* savedHighlight = nullptr;
    // 
    //         //if (savedHighlight) {
    //             //memcpy(E->row[savedHighlightLine].highlight, savedHighlight, E->row[savedHighlightLine].rsize);
    //             //free(savedHighlight);
    //             //savedHighlight = nullptr;
    //         //}
    // 
    //         //if (key == Key::carriageRet || key == Key::escapeSequence) {
    //             //lastMatch = -1;
    //             //direction = 1;
    //         //} else if (key == Key::arrowRight || key == Key::arrowDown) {
    //             //direction = 1;
    //         //} else if (key == Key::arrowLeft || key == Key::arrowUp) {
    //             //direction = 1;
    //         //} else {
    //             //lastMatch = -1;
    //             //direction = 1;
    //         //}
    // 
    //         //if (lastMatch == -1)
    //             //direction = 1;
    // 
    //         //int current = lastMatch;
    //         //for (int i = 0; i < E->numrows; i++) {
    //             //current += direction;
    // 
    //             //if (current == -1)
    //                 //current = E->numrows - 1;
    //             //else if (current == E->numrows)
    //                 //current = 0;
    // 
    //             //Editor::RowData* row = &E->row[current];
    //             //char* match = strstr(row->render, query);
    //             //if (match) {
    //                 //lastMatch = current;
    //                 //E->cy = current;
    //                 //E->cx = RowRxToCx(row, match - row->render);
    //                 //E->rowOff = E->numrows;
    // 
    //                 //savedHighlightLine = current;
    //                 //savedHighlight = new char[row->rsize];
    //                 //memcpy(savedHighlight, row->highlight, row->rsize);
    //                 //memset(&row->highlight[match - row->render], (int)Highlight::match, strlen(query));
    //                 //break;
    //             //}
    //         //}
    //     }
    } // namespace editor
} // namespace sustext
