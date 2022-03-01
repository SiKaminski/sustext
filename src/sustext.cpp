#include "headers/defines.hpp"
#include "headers/data.hpp"
#include "headers/terminal.hpp"
#include "headers/appendbuffer.hpp"
#include "headers/io.hpp"

/*** init ***/
void initEditor(){
	E.cx = 0;
	E.cy = 0;

	if(Terminal::getWindowSize(&E.screenRows, &E.screenCols) == -1) Terminal::die ("getWindowSize");
}

/*** input ***/
void editorMoveCursor(int key){
	switch(key){
		case ARROW_LEFT:
			if(E.cx != 0) E.cx--;
			break;
		case ARROW_RIGHT:
			if(E.cx != E.screenCols - 1) E.cx++;
			break;
		case ARROW_UP:
			if(E.cy != 0) E.cy--;
			break;
		case ARROW_DOWN:
			if(E.cy != E.screenRows - 1) E.cy++;
			break;
	}
}

void editorProcessKeypress(){
	int c = Terminal::editorReadKey();

	switch(c){
		case CTRL_KEY('q'):
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;

		case HOME_KEY:
			E.cx = 0;
			break;
		case END_KEY:
			E.cx = E.screenCols - 1;
			break;

	    case PAGE_UP:
		case PAGE_DOWN:
			{
				int times = E.screenRows;
				while(times--) editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
			}
			break;

		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			editorMoveCursor(c);
			break;
	}
}

/*** output ***/
void editorDrawRows(struct AppendBuffer::abuf *ab) {
	int y;
	for (y = 0; y < E.screenRows; y++) {
		if (y == E.screenRows / 3) {
			char welcome[80];
			int welcomelen = snprintf(welcome, sizeof(welcome),
			  "sustext editor -- version %s", SUSTEXT_VERSION);
			if (welcomelen > E.screenCols) welcomelen = E.screenCols;
			int padding = (E.screenCols - welcomelen) / 2;
			if (padding) {
				abAppend(ab, "~", 1);
				padding--;
		  }
		  while (padding--) abAppend(ab, " ", 1);
		  abAppend(ab, welcome, welcomelen);
		} else {
			abAppend(ab, "~", 1);
		}
		abAppend(ab, "\x1b[K", 3);
		if (y < E.screenRows - 1) {
			abAppend(ab, "\r\n", 2);
		}
	}
}

void editorRefreshScreen(){
	struct AppendBuffer::abuf ab = ABUF_INIT;

	abAppend(&ab, "\x1b[?25l", 6);
	abAppend(&ab, "\x1b[H", 3);

	editorDrawRows(&ab);

	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
	abAppend(&ab, buf, strlen(buf));

	abAppend(&ab, "\x1b[?25h", 6);

	write(STDOUT_FILENO, ab.b, ab.len);
	abFree(&ab);
}

int main(){
	Terminal::enableRawMode();
	initEditor();

	while(1){
		editorRefreshScreen();
		editorProcessKeypress();
	}
	return 0;
}
