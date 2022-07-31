#include "globals.h"
#include "sustext.h"
#include "editor.h"
#include "Debug/logger.h"

uint64_t Flags;
Editor::ConfigData eConfig;
Terminal::ConfigData tConfig;

Logger logger;
int main(int argc, char** argv)
{
	LOG_INIT("logs/", "info")

	LOG_INFO << "Initializing Sustext\n";
	Sustext::Initialize(argc, argv);

    while (true) {
        Editor::RefreshScreen();
        Editor::ProcessKeypress();
    }

	logger.Close();
	return 0;
}
