#include "sustext.hpp"
#include "globals.hpp"

EditorConfig E;
TerminalConfig gTerminalConfig;

int main(int argc, char **argv)
{
    Sustext sustext = Sustext(argc, argv);
    sustext.Initialize();

    while (true) {
        if (sustext.editor.flags.Enabled(FILESAVE))
            sustext.filehandler.SaveFile(&sustext.editor);
            
        sustext.editor.RefreshScreen();
        sustext.editor.ProcessKeypress();
    } 

    return 0;
}