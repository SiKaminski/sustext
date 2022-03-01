#include "headers/sustext.hpp"
#include "headers/defines.hpp"
#include "headers/data.hpp"
#include "headers/io.hpp"

int main(){
    Sustext sustext;
	
	sustext.terminal.enableRawMode();
	sustext.initEditor();

	while(1){
		IO::editorRefreshScreen(sustext.terminal);
		IO::editorProcessKeypress(sustext.terminal);
	}
	return 0;
}