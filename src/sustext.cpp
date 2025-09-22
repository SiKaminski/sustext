#include "sustext.h"
// #include "terminal.h"
// #include "editor.h"
// #include "prototypes.h"
// #include "filehandler.h"
#include "utils/logger.h"
// #include <thread>

namespace Sustext {
void Initialize(int argc, char **argv) {
  logger.Log(INFO, "Initializing Sustext");

  // Editor::Initialize(argc, argv);

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

  logger.Log(SUCCESS, "Initialized Sustext");
}

void Loop() {
  // while (Editor::config.running) {
  //   Editor::RefreshScreen();
  //   Editor::ProcessKeypress();
  // }
  // std::thread tRefreshEditor(Editor::RefreshScreen);
  // std::thread tProcessKeyPressEditor(Editor::ProcessKeypress);

  // tProcessKeyPressEditor.join();
  // tRefreshEditor.join();
}

} // namespace Sustext
