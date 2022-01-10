#include "Input.h"
#include "Output.h"
#include "Terminal.h"

void initEditor(){
	E.cx = 0;
	E.cy = 0;

	if(Terminal::getWindowSize(&E.screenRows, &E.screenCols) == -1) Terminal::die ("getWindowSize");
}

int main(){
	Terminal::enableRawMode();
	initEditor();

	while(1){
		Output::editorRefreshScreen();
		Input::editorProcessKeypress();
	}
	return 0;
}
