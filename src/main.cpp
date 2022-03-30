#include "sustext.hpp"

int main(int argc, char** argv){
    Sustext sustext = Sustext(argc, argv);
    sustext.Initialize();

    while(true){
        sustext.editor.RefreshScreen();
        sustext.editor.ProcessKeypress();
    } 

    return 0;
}