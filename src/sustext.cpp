#include "sustext.h"
//#include "terminal.h"
#include "editor.h"
//#include "prototypes.h"
#include "flaghandler.h"
#include "filehandler.h"
#include "logger.h"
#include <thread>

namespace Sustext 
{
    void Initialize(int argc, char** argv)
    {
        LOG_INFO << "Initializing Sustext" << std::endl;

        Editor::Initialize(argc, argv);


        // Initialize editor and terminal
        //Editor::Initialize(argc, argv);
        //Terminal::EnableRawMode();
        //FlagHandler::Initialize(argc, argv);
        
        //if (FlagHandler::Enabled(FlagHandler::Identifier::fileIn)) {
            //if (!FileHandler::OpenFile(eConfig.filepath))
                //Terminal::die((int)Severity::medium, "fopen");     
        //}    

        //if (FlagHandler::Enabled(FlagHandler::Identifier::modeSus)) {
            // TODO
        //}

        //Editor::SetStatusMessage("HELP: Ctrl-s = save | Ctrl-q = quit | Ctrl-f = find", FindCallBack);

        LOG_SUCCESS << "Initialized Sustext" << std::endl;
    }

    void Loop()
    {
        while (Editor::config.running) {
            Editor::ProcessKeypress();
            Editor::RefreshScreen();
        }
        //std::thread tRefreshEditor(Editor::RefreshScreen);
        //std::thread tProcessKeyPressEditor(Editor::ProcessKeypress);

        //tProcessKeyPressEditor.join();
        //tRefreshEditor.join();
    }

}
