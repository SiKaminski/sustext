#include "headers/terminal.hpp"

void Terminal::disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void Terminal::enableRawMode(){
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(+[this]{this.disableRawMode();});
    termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}