#include "headers/sustext.hpp"

Sustext::Sustext(){
}

void Sustext::initEditor(){
	E.cx = 0;
	E.cy = 0;

	if(terminal.getWindowSize(&E.screenRows, &E.screenCols) == -1) terminal.die ("getWindowSize");
}
