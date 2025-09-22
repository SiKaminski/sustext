#include "utils/logger.hpp"
#include "editor.hpp"

using namespace Sustext;

//uint64_t Flags;
//Editor::Config eConfig;
//Terminal::Config tConfig;

Editor* Editor::instancePtr = nullptr;
std::mutex Editor::mtx;
Logger logger;

int main(int argc, char** argv)
{
    logger = Logger("logs/", "info"); 
    logger.Log(INFO, "Initializing Sustext");
    
    // Editor::Initialize(argc, argv);
    Editor* editor = Editor::getInstance();
    editor->Initialize();

    // Initialize editor and terminal
    // Terminal::EnableRawMode();
    // FlagHandler::Initialize(argc, argv);

    // if (FlagHandler::Enabled(FlagHandler::Identifier::fileIn)) {
    // if (!FileHandler::OpenFile(eConfig.filepath))
    // Terminal::die((int)Severity::medium, "fopen");
    //}

    // if (FlagHandler::Enabled(FlagHandler::Identifier::modeSus)) {
    //  TODO
    //}

    // Editor::SetStatusMessage("HELP: Ctrl-s = save | Ctrl-q = quit | Ctrl-f =
    // find", FindCallBack);
    // Editor::DumpState();

    logger.Log(SUCCESS, "Initialized Sustext");

    // while (Editor::config.running) {
    //   Editor::RefreshScreen();
    //   Editor::ProcessKeypress();
    // }
    // std::thread tRefreshEditor(Editor::RefreshScreen);
    // std::thread tProcessKeyPressEditor(Editor::ProcessKeypress);

    // tProcessKeyPressEditor.join();
    // tRefreshEditor.join();

	logger.Close();
	return 0;
}
