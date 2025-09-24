#include "signals.hpp"
#include "editor.hpp"

#include <iostream>
#include <termios.h>

void Sustext::SigIntHandler(int sig)
{
    std::cerr << "TODO: Handle sigint properly\n\r";
    std::cerr << "Sig int got: " << sig << "\n\r";
    exit(-1);
}

// Clean up ncurses terminal attributes to use original attrs before program
// was ran
void Sustext::Cleanup()
{
    Editor::Editor* editor = Editor::Editor::getInstance();
    termios* origTermAttrs = editor->GetOrigTermAttr();

	//Clear screen on exit
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
    
    if (tcsetattr(STDOUT_FILENO, 0, origTermAttrs) != 0) {
        std::cerr << "Unable to set original terminal attributes\n\r";
        exit(1); 
    }

    exit(0); 
}
