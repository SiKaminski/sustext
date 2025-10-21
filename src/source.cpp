#include "utils/logger.hpp"
#include "utils/skutilflagparser.hpp"
#include "utils/common.hpp"
#include "editor.hpp"
#include "signals.hpp"

using namespace Sustext;

Editor::Editor* Editor::Editor::instancePtr = nullptr;
Editor::Editor* editor = nullptr;
std::mutex Editor::Editor::mtx;
Logger logger;

//uint64_t Flags;
//Terminal::Config tConfig;

void SusMode(OPT int inputCount, OPT char** intputVals)
{
    logger.Log(INFO, "SUSSY!!!\n");
    Editor::EditorConfig* cfg = editor->GetConfig();
    cfg->mode = Editor::Mode::SUS;
    editor->SetConfig(cfg);
}

SKUTIL::SK_VEC<SKUTIL::Flag> flags {
    {
        's',
        "sus",
        "Enter Sus mode (Sussy)",
        0,
        SusMode,
    },
};

int main(int argc, char** argv)
{
    logger = Logger("logs/", "info"); 
    logger.Log(INFO, "Initializing Sustext");

    if (atexit(Sustext::Cleanup) != 0) {
        logger.Log(ERROR, "Unable to bind exit function");
        exit(1);
    }

    // Setup flags
    SKUTIL::FlagParser parser = SKUTIL::FlagParser(&flags);
    parser.ParseFlags(argc, argv);
    
    editor = Editor::Editor::getInstance();
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
