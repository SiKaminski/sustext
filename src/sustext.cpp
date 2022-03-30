#include "sustext.hpp"

Sustext::Sustext(int _argc, char** _argv){
	argc = _argc;
	argv = _argv;
}

Sustext::~Sustext(){}

int Sustext::Initialize(){
	editor.Init(argc, argv);
	Terminal::enableRawMode();

	if(argc >= 2){
		if(editor.flags.Enabled(FILEIN)){
			if(!filehandler.OpenFile(editor.flags.argout.filepath, &editor)){
				Terminal::die("fopen");
			}
		}
	}

	editor.SetStatusMessage("HELP: Ctrl-s = save | Ctrl-q = quit");

	return 1;
}