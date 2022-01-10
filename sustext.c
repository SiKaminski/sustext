#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

/*** init ***/
void initEditor(){
	E.cx = 0;
	E.cy = 0;

	if(getWindowSize(&E.screenRows, &E.screenCols) == -1) die ("getWindowSize");
}

int main(){
	enableRawMode();
	initEditor();

	while(1){
		editorRefreshScreen();
		editorProcessKeypress();
	}
	return 0;
}
