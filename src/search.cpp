#include "search.hpp"

void Find(EditorConfig E){
    int savedCx = E.cx;
	int savedCy = E.cy;
	int savedColOff = E.colOff;
	int savedRowOff = E.rowOff;
    char*(Editor::*fp)(char*, FindCallback)
	char* query = fp;
	if(query == NULL) return;
	
	if(query){
		free(query);
	} else {
		E.cx = savedCx;
		E.cy = savedCy;
		E.colOff = savedColOff;
		E.rowOff = savedRowOff;
	}
}

void FindCallback(char* query, int key, EditorConfig E){
	fprintf(stderr, "Bruh callback");
	
	static int last_match = -1;
	static int direction = 1;

	if(key == '\r' || key == '\x1b'){
		last_match = -1;
		direction = 1;
		return;
	} else if(key == ARROW_RIGHT || key == ARROW_DOWN){
		direction = 1;
	} else if(key == ARROW_LEFT || key == ARROW_UP){
		direction = -1;
	} else {
		last_match = -1;
		direction = 1;
	}

	if(last_match == -1) direction = 1;
	int current = last_match;
	
	for(int i = 0; i < E.numrows; i++){
		current += direction;
		if(current = -1) current = E.numrows - 1;
		else if(current == E.numrows) current = 0;		
		erow* row = &E.row[current];
		char* match = strstr(row->render, query);
		if(match){
			last_match = current;
			E.cy = current;
			E.cx = Editor::RowRxToCX(row, match - row->render, E);
			E.rowOff = E.numrows;
			break;
		}
    }
}