#include "headers/Terminal.hpp"

void Terminal::die(const char* s)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}

void Terminal::disableRawMode(Data::EditorConfig E){
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) die("tcsetattr");
}

void Terminal::enableRawMode(Data::EditorConfig E){

}