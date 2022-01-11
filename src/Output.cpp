#include "Output.h"

namespace Output{
	using namespace AppendBuffer; // Might need to rework to not do this
	void editorDrawRows(struct abuf *ab) {
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
		struct abuf ab = ABUF_INIT;

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
}