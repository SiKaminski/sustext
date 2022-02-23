#include "headers/sustext.hpp"
#include "headers/defines.hpp"
#include "headers/data.hpp"

int main(){
    Sustext sustext;
    sustext.terminal.enableRawMode();

    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');

    return 0;
}