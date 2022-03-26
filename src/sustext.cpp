#include "headers/defines.hpp"
#include "headers/data.hpp"
#include "headers/terminal.hpp"
#include "headers/appendbuffer.hpp"
#include "headers/editor.hpp"
#include "headers/editorflags.hpp"

int main(int argc, char** argv){
	SusFlags sFlags = SusFlags(argc, argv);
	Terminal::enableRawMode();
	Editor::Init();

	//Check if parameters
	if(argc >= 2){
		sFlags.SetFlags();

		if(sFlags.Enabled(FILEIN))
			Editor::OpenFile(sFlags.argout.filepath);
	}

	while(1){
		Editor::RefreshScreen();
		Editor::ProcessKeypress();
	}
	return 0;
}
