#include "sustext.h"
#include "editor.h"
#include "logger.h"

//uint64_t Flags;
//Editor::Config eConfig;
//Terminal::Config tConfig;

Logger logger;
int main(int argc, char** argv)
{
    using namespace Sustext;
	LOG_INIT("logs/", "info")

	Sustext::Initialize(argc, argv);
    Editor::DumpState();
    Sustext::Loop();


    //Editor::DumpState();
    //while (true) {
        //Editor::RefreshScreen();
        ////Editor::ProcessKeypress();
    //}

	logger.Close();
	return 0;
}
