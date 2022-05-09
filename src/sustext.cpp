#include "globals.h"
#include "sustext.h"
#include "terminal.h"
#include "editor.h"

Editor::ConfigData eConfig;
Terminal::ConfigData tConfig;

int main(int argc, char** argv)
{
	Sustext::Initialize(argc, argv);

	while (true) {
		/*
			check for flags
		*/

		// Editor refresh screen
		// editor process key
	}

	return 0;
}

void Sustext::Initialize(int argc, char** argv)
{
	// Initialize editor
	// Enable raw mode (terminal)

	if (argc >= 2) {
		// Check for file in

		// Check for other terminal flags
	}

	// set editor status message
}


// Sustext::Sustext(int _argc, char** _argv){
// 	argc = _argc;
// 	argv = _argv;
// }

// Sustext::~Sustext() {}

// int Sustext::Initialize(){
// 	editor.Init(argc, argv);
// 	Terminal::enableRawMode();

// 	if(argc >= 2){
// 		if(editor.flags.Enabled(FILEIN)){
// 			if(!filehandler.OpenFile(editor.flags.argout.filepath, &editor)){
// 				Terminal::die("fopen");
// 			}
// 		}
// 	}

// 	editor.SetStatusMessage("HELP: Ctrl-s = save | Ctrl-q = quit | Ctrl-f = find", FindCallBack);

// 	return 1;
// }