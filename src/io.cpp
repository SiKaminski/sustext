#include "headers/io.hpp"

void IO::initEditor(){
	E.cx = 0;
	E.cy = 0;
	E.numrows = 0;
	if(Terminal::getWindowSize(&E.screenRows, &E.screenCols) == -1) Terminal::die("getWindowSize");
}

/*** input ***/
void IO::editorMoveCursor(int key){
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

void IO::editorOpen(char* filename){
	FILE* fp = fopen(filename, "r");
	if(!fp) Terminal::die("fopen");

	char* line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	linelen = getline(&line, &linecap, fp);
	if(linelen != -1){
		while(linelen > 0 && (line[linelen - 1] == '\n' ||
		line[linelen - 1] == '\r'))
			linelen--;

	E.row.size = linelen;
	E.row.chars = (char*)malloc(linelen + 1);
	memcpy(E.row.chars, line, linelen);
	E.row.chars[linelen] = '\0';
	E.numrows = 1;
	}
	free(line);
	fclose(fp);
}

void IO::editorProcessKeypress(){
	int c = Terminal::editorReadKey();

	switch(c){
		case CTRL_KEY('q'):

			//[2J will erase all of the diaply without moving the cursor position
			write(STDOUT_FILENO, "\x1b[2J", 4);

			//Return cursor to home
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;

		case HOME_KEY:
		case END_KEY:
			{
				int times = E.screenCols;
				while(times--) editorMoveCursor(c == HOME_KEY ? ARROW_LEFT : ARROW_RIGHT);
			}
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
void IO::editorDrawRows(struct AppendBuffer::abuf *ab) {
	int y;
	for (y = 0; y < E.screenRows; y++) {
		if(y >= E.numrows){
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
		} else {
			int len = E.row.size;
			if(len > E.screenCols) len = E.screenCols;
			AppendBuffer::abAppend(ab, E.row.chars, len);
		}
		abAppend(ab, "\x1b[K", 3);
		if (y < E.screenRows - 1) {
			abAppend(ab, "\r\n", 2);
		}
	}
}

void IO::editorRefreshScreen(){
	struct AppendBuffer::abuf ab = ABUF_INIT;

	//Use the ?25l esacape sequence to hide to cursor on refresh
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
