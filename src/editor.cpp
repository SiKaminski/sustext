#include "headers/editor.hpp"

/*---- INITIALIZATION ----*/
void Editor::Init(){
	/* Set default values for the global editorConfig struct */
	E.cx = 0;
	E.cy = 0;
	E.rowOff = 0; // Scroll to the top of the file by default
	E.colOff = 0; // Scroll cursor to the left of the screen by default 
	E.numrows = 0;
	E.row = new erow{0,NULL};
	if(Terminal::getWindowSize(&E.screenRows, &E.screenCols) == -1) Terminal::die("getWindowSize");
}

/*---- ROW OPERATIONS ----*/
void Editor::AppendRow(char* s, size_t len){
	E.row = (erow*)realloc(E.row, sizeof(erow) * (E.numrows + 1));

	int at = E.numrows;
	E.row[at].size = len;
	E.row[at].chars = (char*)malloc(len+1);

	memcpy(E.row[at].chars, s, len);
	E.row[at].chars[len] = '\0';
	E.numrows++;
}

/*---- INPUT ----*/
void Editor::MoveCursor(int key){
	//Prevent cursor from going past the size of the screen not the file
	erow* row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];

	switch(key){
		case ARROW_LEFT:
			if(E.cx != 0) E.cx--;
			break;
		case ARROW_RIGHT:
			if(row && E.cx < row->size) E.cx++;
			break;
		case ARROW_UP:
			if(E.cy != 0) E.cy--;
			break;
		case ARROW_DOWN:
			if(E.cy < E.numrows) E.cy++;
			break;
	}
}

void Editor::OpenFile(char* filename){
	//Open a file in read mode
	FILE* fp = fopen(filename, "r");
	if(!fp) Terminal::die("fopen");

	char* line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	//Get the line at index 0 of the file
	linelen = getline(&line, &linecap, fp);

	//Get the length of the line from the file
	while((linelen = getline(&line, &linecap, fp)) != -1){
		//stop if the escape sequence for new line or return carriage is next
		while(linelen > 0 && (line[linelen - 1] == '\n' ||
		line[linelen - 1] == '\r'))
			linelen--;
		AppendRow(line, linelen);
	}
	//Deallocate memory from line and close file connection
	free(line);
	fclose(fp);
}

void Editor::ProcessKeypress(){
	int c = Terminal::editorReadKey();

	// Bane of my existance
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
				//Once horizontal scrolling is enabled, this will be relative to the columns
				//visible on the screen
				int times = E.screenCols;
				while(times--) MoveCursor(c == HOME_KEY ? ARROW_LEFT : ARROW_RIGHT);
			}
			break;

	    case PAGE_UP:
		case PAGE_DOWN:
			{
				//Once Scrolling is enabled, This will have to be relative to the amount of
				//Rows visible on the screen
				int times = E.screenRows;
				while(times--) MoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
			}
			break;

		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			MoveCursor(c);
			break;
	}
}

/*---- OUTPUT ----*/
void Editor::Scroll(){
	if(E.cy < E.rowOff){
		E.rowOff = E.cy;
	}
	if(E.cy >= E.rowOff + E.screenRows){
		E.rowOff = E.cy - E.screenRows + 1;
	}
	if(E.cx < E.colOff){
		E.colOff = E.cx;
	}
	if(E.cx >= E.colOff + E.screenCols){
		E.colOff = E.cx - E.screenCols + 1;

	}
}

void Editor::DrawRows(struct AppendBuffer::abuf *ab) {
	for(int y = 0; y < E.screenRows; y++) {
		int filerow = y + E.rowOff;
		if(filerow >= E.numrows){
			// Prepare the append buffer
			if (E.numrows == 0 && y == E.screenRows / 3) {
				// The welcome text will only show if the editor is opened as a standalone
				// program with no inputs, on file open there is no welcome
				char welcome[80];
				int welcomelen = snprintf(welcome, sizeof(welcome),
				  "sustext editor -- version %s", SUSTEXT_VERSION);
				if (welcomelen > E.screenCols) welcomelen = E.screenCols;
				int padding = (E.screenCols - welcomelen) / 2;

				// Padding will always be present on blank lines
				if (padding) {
					abAppend(ab, "~", 1);
					padding--;
			  	}
			  while (padding--) abAppend(ab, " ", 1);
			  abAppend(ab, welcome, welcomelen);
			} else { abAppend(ab, "~", 1); }
		} else {
			int len = E.row[filerow].size - E.colOff;
			// Prevent the length for being a negative number
			if(len < 0) len = 0;
			if(len > E.screenCols) len = E.screenCols;
			AppendBuffer::abAppend(ab, E.row[filerow].chars, len);
		}

		// Since everything for the row is appended to the buffer everything 
		// after the cursor which effecively produces a clean row
		abAppend(ab, "\x1b[K", 3);

		// Account for the last row
		if (y < E.screenRows - 1) { abAppend(ab, "\r\n", 2); }
	}
}

void Editor::RefreshScreen(){
	Scroll();
	struct AppendBuffer::abuf ab = ABUF_INIT;

	// Use the ?25l esacape sequence to hide to cursor on refresh
	abAppend(&ab, "\x1b[?25l", 6);
	abAppend(&ab, "\x1b[H", 3);

	DrawRows(&ab);

	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cy - E.rowOff) + 1, (E.cx - E.colOff) + 1);
	abAppend(&ab, buf, strlen(buf));

	abAppend(&ab, "\x1b[?25h", 6);

	write(STDOUT_FILENO, ab.b, ab.len);
	abFree(&ab);
}