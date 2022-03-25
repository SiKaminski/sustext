#include "headers/defines.hpp"
#include "headers/data.hpp"
#include "headers/terminal.hpp"
#include "headers/appendbuffer.hpp"
#include "headers/editor.hpp"
#include "headers/flags.hpp"

int main(int argc, char** argv){
	Terminal::enableRawMode();
	Editor::Init();

	//Check if parameters
	if(argc >= 2){
		Editor::InitFlags(argc, argv);
		fprintf(stderr, "Opening: %s\n", Editor::argout.filepath);
		if(Editor::argFlags.fileIn){
			Editor::OpenFile(Editor::argout.filepath);
			exit(1);
		}

		// Editor::OpenFile(argv[1]);
	}

	while(1){
		Editor::RefreshScreen();
		Editor::ProcessKeypress();
	}
	return 0;
}
