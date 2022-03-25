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
		using namespace SustextArgs;
		SustextArgs::InitFlags(argc, argv);
		
		if(flags.fileIn){
			Editor::OpenFile(argOuts.filepath);
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
