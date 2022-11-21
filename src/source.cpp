#include "sustext.h"
#include "editor.h"
#include "terminal.h"
#include "logger.h"

//uint64_t Flags;
//Editor::Config eConfig;
//Terminal::Config tConfig;

Logger logger;
int main(int argc, char** argv)
{
	LOG_INIT("logs/", "info")

	Sustext::Initialize(argc, argv);

    Editor::DumpState();
    //while (true) {
        //Editor::RefreshScreen();
        //Editor::ProcessKeypress();
    //}

	logger.Close();
	return 0;
}
