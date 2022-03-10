#include "headers/defines.hpp"
#include "headers/data.hpp"
#include "headers/terminal.hpp"
#include "headers/appendbuffer.hpp"
#include "headers/io.hpp"

int main(){
	Terminal::enableRawMode();
	IO::initEditor();

	while(1){
		IO::editorRefreshScreen();
		IO::editorProcessKeypress();
	}
	return 0;
}
