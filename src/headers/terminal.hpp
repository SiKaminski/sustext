#pragma once
#ifndef _SUSTEXT_TERMINAL_HPP_
#define _SUSTEXT_TERMINAL_HPP_

#include <termios.h>
#include <mutex>
//#include <ncurses.h>
//#include "editor.h"

namespace Sustext
{
    namespace Terminal
    {
        enum State : int {
            HOME,
            EDIT,
            READ_ONLY,
            WELCOME,
        };

        struct TerminalConfig {  
            termios OrigTermios;
            State   state; 
        };

        // Singleton Class
        class Terminal 
        {
            public:
                Terminal(const Terminal* obj) = delete;

                static Terminal* getInstance() {
                    if (instancePtr == nullptr) {
                        std::lock_guard<std::mutex> lock(mtx);
                        if (instancePtr == nullptr) {
                            instancePtr = new Editor();
                        }
                    }

                    return instancePtr;
                }

                void Initialize();

                /**
                * exit the program with a message to display what error occured 
                * 
                * @param s error message
                */
                void Die(const int severity, const char* s);

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
                int GetCursorPosition(int* rows, int* cols);

                /**
                * Get the Window Size of the terminal
                * 
                * @param rows (int) value to store row information  
                * @param cols (int) value to store column information
                * @return (int) exit status: 0 = success
                */
                int GetWindowSize(int* rows, int* cols);

                TerminalConfig* GetConfig();
                void SetConfig(TerminalConfig* newCfg);
                termios* GetOrigTermAttr();

            private:

                /**
                * Put the terminal window back to the origional state it was
                * at before (from raw input to canonical mode (cooked mode)) 
                */
                void DisableRawMode();

                /**
                * Enable raw input mode for the terminal by enabling and disabling
                * canonical flags
                */
                void EnableRawMode();

                Terminal() {}

            private:
                TerminalConfig* mConfig;

                // This should be in the terminal class but this works for now
                termios* mOrigTerm;
                
                // Static pointer to the editor instance
                static Terminal* instancePtr;

                // Mutex for thread saftey
                static std::mutex mtx;
        };
    } // namespace Terminal
}

#endif // _SUSTEXT_TERMINAL_HPP_
