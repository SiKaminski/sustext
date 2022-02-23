#include "headers/terminal.hpp"

Terminal::Terminal(){

}

void Terminal::disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios);
}

void Terminal::enableRawMode(){
    tcgetattr(STDIN_FILENO, &E.orig_termios);
    atexit(disableRawMode);
    termios raw = E.orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}