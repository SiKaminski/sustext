#include "headers/defines.hpp"
#include "headers/data.hpp"
#include "headers/terminal.hpp"
#include "headers/appendbuffer.hpp"
#include "headers/io.hpp"

int main(int argc, char** argv){
	Terminal::enableRawMode();
	IO::initEditor();

	if(argc >= 2){
		IO::editorOpen(argv[1]);
	}

	while(1){
		IO::editorRefreshScreen();
		IO::editorProcessKeypress();
	}
	return 0;
}
