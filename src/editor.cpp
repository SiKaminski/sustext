#include "headers/editor.hpp"
#include "global.hpp"

Editor::Editor() {}
Editor::~Editor() {}

/*---- INITIALIZATION ----*/
void Editor::Init(int argc, char** argv){
	flags.InitFlags(argc, argv);
	/* Set default values for the global editorConfig struct */
	E.cx = 0;
	E.cy = 0;
	E.rx = 0;
	E.rowOff = 0;
	E.colOff = 0;
	E.numrows = 0;
	E.row = new erow{0, 0, NULL, NULL};
	E.filepath = NULL;
	E.statusmsg[0] = '\0';
	E.statusmsg_time = 0;
	E.dirty = 0;

	if(Terminal::getWindowSize(&E.screenRows, &E.screenCols) == -1) Terminal::die("getWindowSize");
	E.screenRows -= 2; //Account for status bar sapce so it won't be drawn over
}

/*---- ROW OPERATIONS ----*/
int Editor::RowCxToRx(erow* row, int cx){
	int rx = 0;
	for(int i = 0; i < cx; i++){
		// Check to see how many columns to the left of the next tab the cursor is
		if(row->chars[i] == '\t')
			rx += (SUSTEXT_TAB_STOP - 1) - (rx % SUSTEXT_TAB_STOP);
		rx++;
	}
	
	return rx;
}

char* Editor::Prompt(char* prompt){
	size_t bufsize = 128;
	char* buf = (char*)malloc(bufsize);

	size_t buflen = 0;
	buf[0] = '\0';

	while(1){
		SetStatusMessage(prompt, buf);
		RefreshScreen();

		int c = Terminal::editorReadKey();

		//Check if user is removing a character
		if(c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE){
			if(buflen != 0) buf[--buflen] = '\0';
		} else if(c == '\x1b') {
			SetStatusMessage("");
			free(buf);
			return NULL;
		} else if(c == '\r') {
			if(buflen != 0){
				SetStatusMessage("");
				return buf;
			}
		} else if(!iscntrl(c) && c < 128) {
			if(buflen == bufsize - 1){
				bufsize *= 2;
				buf = (char*)realloc(buf, bufsize);
			}
			buf[buflen++] = c; 
			buf[buflen] = '\0';
		}
	}
}

void Editor::UpdateRow(erow* row){
	int tabs = 0;
	for(int j = 0; j < row->size; j++){
		if(row->chars[j] == '\t') tabs++;
	}

	free(row->render);
	row->render = (char*)malloc(row->size + tabs*(SUSTEXT_TAB_STOP - 1) + 1);

	int i = 0;
	for(int j = 0; j < row->size; j++){
		if(row->chars[j] == '\t'){
			row->render[i++] = ' ';
			while(i % SUSTEXT_TAB_STOP != 0) row->render[i++] = ' ';
		} 
		else row->render[i++] = row->chars[j];
	}
	row->render[i] = '\0';
	row->rsize = i;
}

void Editor::InsertRow(int at, char* s, size_t len){
	if(at < 0 || at > E.numrows) return;
	E.row = (erow*)realloc(E.row, sizeof(erow) * (E.numrows + 1));
	memmove(&E.row[at + 1], &E.row[at], sizeof(erow) * (E.numrows - at));

	E.row[at].size = len;
	E.row[at].chars = (char*)malloc(len+1);

	memcpy(E.row[at].chars, s, len);
	E.row[at].chars[len] = '\0';

	// Initialize render for buffer
	E.row[at].rsize = 0;
	E.row[at].render = NULL;
	UpdateRow(&E.row[at]);

	E.numrows++;
	E.dirty++;
}

void Editor::RowInsertChar(erow* row, int at, int c){
    if(at < 0 || at > row->size) at = row->size;
	row->chars = (char*)realloc(row->chars, row->size + 2);
    memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);
    row->size++;
    row->chars[at] = c;
    UpdateRow(row);
	E.dirty++;
}

void Editor::InsertChar(int c){
	if(E.cy == E.numrows) InsertRow(E.numrows, (char*)"", 0);
	RowInsertChar(&E.row[E.cy], E.cx, c);
	E.cx++;
}

void Editor::InsertNewLine(){
	if(E.cx == 0) InsertRow(E.cy, (char*)"", 0);
	else {
		erow* row = &E.row[E.cy];
		InsertRow(E.cy + 1, &row->chars[E.cx], row->size - E.cx);
		row = &E.row[E.cy];
		row->size = E.cx;
		row->chars[row->size] = '\0';
		UpdateRow(row);
	}

	E.cy++;
	E.cx = 0;
}

void Editor::RowAppendString(erow* row, char* str, size_t len){
	row->chars = (char*)realloc(row->chars, row->size + len + 1);
	memcpy(&row->chars[row->size], str, len);
	row->size += len;
	row->chars[row->size] = '\0';
	UpdateRow(row);
	E.dirty++;
}


void Editor::DeleteRow(int at){
	if(at < 0 || at >= E.numrows) return;
	FreeRow(&E.row[at]);
	memmove(&E.row[at], &E.row[at + 1], sizeof(erow) * (E.numrows - at - 1));
	E.numrows--;
	E.dirty++;
}

void Editor::RowDeleteChar(erow* row, int at){
	if(at < 0 || at >= row->size) return;
	memmove(&row->chars[at], &row->chars[at + 1], row->size - at);
	row->size--;
	UpdateRow(row);
	E.dirty++;
}

void Editor::DeleteChar(){
	if(E.cy == E.numrows) return;
	if(E.cx == 0 && E.cy == 0) return;

	erow* row = &E.row[E.cy];
	if(E.cx > 0){
		RowDeleteChar(row, E.cx - 1);
		E.cx--;
	} else {
		E.cx = E.row[E.cy - 1].size;
		RowAppendString(&E.row[E.cy - 1], row->chars, row->size);
		DeleteRow(E.cy);
		E.cy--;
	}
}

void Editor::FreeRow(erow* row){
	free(row->render);
	free(row->chars);
}

/*---- INPUT ----*/
void Editor::MoveCursor(int key){
	//Prevent cursor from going past the size of the screen not the file
	erow* row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];

	switch(key){
		case ARROW_LEFT:
			if(E.cx != 0) E.cx--;
			else if(E.cy > 0){
				E.cy--;
				E.cx = E.row[E.cy].size;
			}
			break;
		case ARROW_RIGHT:
			if(row && E.cx < row->size) E.cx++;
			else if(row && E.cx == row->size){
				E.cy++;
				E.cx = 0;
			}
			break;
		case ARROW_UP:
			if(E.cy != 0) E.cy--;
			break;
		case ARROW_DOWN:
			if(E.cy < E.numrows) E.cy++;
			break;
	}

	// Cursor snap to end of line
	row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
	int rowlen = row ? row->size : 0;
	if(E.cx > rowlen){ E.cx = rowlen; }
}

void Editor::ProcessKeypress(){
	static int quit_times = SUSTEXT_QUIT_TIMES;
	int c = Terminal::editorReadKey();

	// Bane of my existance
	switch(c){
		case '\r':
			InsertNewLine();
			break;
		case CTRL_KEY('q'):
			if(E.dirty && quit_times > 0){
				SetStatusMessage("File has unsaved changes. "
				"Press Ctrl-Q %d more time(s) to confirm.", quit_times);
				quit_times--;
				return;
			}

			//[2J will erase all of the diaply without moving the cursor position
			write(STDOUT_FILENO, "\x1b[2J", 4);

			//Return cursor to home
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;

		case CTRL_KEY('s'):
			flags.SetFlags(FILESAVE, true);
			return;

		case HOME_KEY:
			E.cx = 0;
			break;
		case END_KEY:	
			if(E.cx < E.numrows)
				E.cx = E.row[E.cy].size;
			break;

		case BACKSPACE:
		case CTRL_KEY('h'):
		case DEL_KEY:
			if(c == DEL_KEY) MoveCursor(ARROW_RIGHT);
			DeleteChar();
			break;

	    case PAGE_UP:
		case PAGE_DOWN:
			if(c == PAGE_UP){
				E.cy = E.rowOff;
			} else if (c == PAGE_DOWN){
				E.cy = E.rowOff + E.screenRows - 1;
				if(E.cy > E.numrows) E.cy = E.numrows;
			}
			break;

		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			MoveCursor(c);
			break;
		
		case CTRL_KEY('l'):
		case '\x1b':
			break;

		default:
			InsertChar(c);
			break;
	}
	quit_times = SUSTEXT_QUIT_TIMES;
}

char* Editor::RowToString(int* buflen){
    int totalLen = 0;
    for(int i = 0; i < E.numrows; i++)
        totalLen += E.row[i].size + 1;
    *buflen = totalLen;

    char* buf = (char*)malloc(totalLen);
    char* ptr = buf;

    for(int i = 0; i < E.numrows; i++){
        memcpy(ptr, E.row[i].chars, E.row[i].size);
        ptr += E.row[i].size;
        *ptr = '\n';
        ptr++;
    }

    fprintf(stderr, "buf out: %s\n", (char*)buf);
    return buf;
}

/*---- OUTPUT ----*/
void Editor::Scroll(){
	E.rx = 0;
	if(E.cy < E.numrows){
		E.rx = RowCxToRx(&E.row[E.cy], E.cx);
	}
	if(E.cy < E.rowOff){
		E.rowOff = E.cy;
	}
	if(E.cy >= E.rowOff + E.screenRows){
		E.rowOff = E.cy - E.screenRows + 1;
	}
	if(E.rx < E.colOff){
		E.colOff = E.rx;
	}
	if(E.rx >= E.colOff + E.screenCols){
		E.colOff = E.rx - E.screenCols + 1;

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
			int len = E.row[filerow].rsize - E.colOff;
			// Prevent the length for being a negative number
			if(len < 0) len = 0;
			if(len > E.screenCols) len = E.screenCols;
			AppendBuffer::abAppend(ab, &E.row[filerow].render[E.colOff], len);
		}

		// Since everything for the row is appended to the buffer everything 
		// after the cursor which effecively produces a clean row
		abAppend(ab, "\x1b[K", 3);

		// Account for the last row
		abAppend(ab, "\r\n", 2);
	}
}

void Editor::DrawStatusBar(struct AppendBuffer::abuf* ab){
	AppendBuffer::abAppend(ab, "\x1b[7m", 4);
	char status[80], rstatus[80];
	int len = snprintf(status, sizeof(status), "%.20s - %d lines %s",
		E.filepath ? E.filepath : "[No Name]", E.numrows,
		E.dirty ? "(modified)" : "");
	int rlen = snprintf(rstatus, sizeof(rstatus), "%d:%d,%d",
		E.cy + 1, E.rx + 1, E.numrows);
	if(len > E.screenCols) len = E.screenCols;
	
	AppendBuffer::abAppend(ab, status, len);
	while(len < E.screenCols){
		if(E.screenCols - len == rlen){
			AppendBuffer::abAppend(ab, rstatus, rlen);
			break;
		} else {
			AppendBuffer::abAppend(ab, " ", 1);
			len++;
		}
	}
	AppendBuffer::abAppend(ab, "\x1b[m", 3);
	AppendBuffer::abAppend(ab, "\r\n", 2);
}

void Editor::DrawMessageBar(AppendBuffer::abuf* ab){
	AppendBuffer::abAppend(ab, "\x1b[K", 3);
	int msglen = strlen(E.statusmsg);
	if(msglen > E.screenCols) msglen = E.screenCols;
	if(msglen && time(NULL) - E.statusmsg_time < 5)
		AppendBuffer::abAppend(ab, E.statusmsg, msglen);
}

void Editor::RefreshScreen(){
	Scroll();
	struct AppendBuffer::abuf ab = ABUF_INIT;

	// Use the ?25l esacape sequence to hide to cursor on refresh
	abAppend(&ab, "\x1b[?25l", 6);
	abAppend(&ab, "\x1b[H", 3);

	DrawRows(&ab);
	DrawStatusBar(&ab);
	DrawMessageBar(&ab);

	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cy - E.rowOff) + 1, (E.rx - E.colOff) + 1);
	abAppend(&ab, buf, strlen(buf));

	abAppend(&ab, "\x1b[?25h", 6);

	write(STDOUT_FILENO, ab.b, ab.len);
	abFree(&ab);
}
    
void Editor::SetStatusMessage(const char* fmt...){
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);
	va_end(ap);
	E.statusmsg_time = time(NULL);
}