#include "headers/terminal.hpp"
#include "global.hpp"

void Terminal::die(const char* s){
	//Clear screen on exit
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);

	perror(s);
	exit(1);
}

void Terminal::disableRawMode(){
	//Set the attributes of the terminal back to its origional state
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) die("tcsetattr");
	system("clear");
}

void Terminal::enableRawMode(){
	//Store origional termios attribs, if there is an error disable raw mode and exit
	if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
	atexit(disableRawMode);

	//Define a new terminal
	struct termios raw = E.orig_termios;

	//Disable flags to leave canonical mode
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	//Set the new terminal
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int Terminal::editorReadKey(){
	int nread;
	char c;
	while((nread = read(STDIN_FILENO , &c, 1)) != 1){
		if(nread == -1 && errno != EAGAIN) die("read");
	}

	//Check for escape sequence
	if (c == '\x1b'){
		//Get a 3 byte buffer for the escape code
		char seq[3];

		if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
		if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
		
		//'27'
		if(seq[0] == '['){
			if(seq[1] >= '0' && seq[1] <= '9'){
				if(read(STDOUT_FILENO, &seq[2], 1) != 1) return '\x1b';
				if(seq[2] == '~'){
					switch(seq[1]){
						case '1': return HOME_KEY;
						case '3': return DEL_KEY;
						case '2': return END_KEY;
						case '5': return PAGE_UP;
						case '6': return PAGE_DOWN;
						case '7': return HOME_KEY;
						case '8': return END_KEY;
					}
				}
			} else {
				//There has to be a better way of implementing keypresses right?
				switch(seq[1]){
					case 'A': return ARROW_UP;
					case 'B': return ARROW_DOWN;
					case 'C': return ARROW_RIGHT;
					case 'D': return ARROW_LEFT;
					case 'H': return HOME_KEY;
					case 'F': return END_KEY;
				}
			}
		} else if (seq[0] == 'O'){
			switch(seq[1]){
				case 'H': return HOME_KEY;
				case 'F': return END_KEY;
			}
		}
		return '\x1b';
	} else return c;
}

int Terminal::getCursorPosition(int* rows, int* cols){
	char buf[32];
	unsigned int i = 0;

	//Failed to provide a position
	if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

	while(i < sizeof(buf) - 1){
		if(read(STDIN_FILENO, &buf[i], 1) != 1) break;
		if(buf[i] == 'R') break;
		i++;
	}
	buf[i] = '\0';
	
	//What the escape sequence doin?
	if(buf[0] != '\x1b' || buf[1] != '[') return -1;

	//If &buf[2] does not have the screen size then zad :(
	if(sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

	return 0;
}

int Terminal::getWindowSize(int* rows, int* cols){
	struct winsize ws;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){
		//Make sure the curusor reaches the bottom right of the screen
		if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
		return getCursorPosition(rows, cols);
	} 
	else{
		*cols = ws.ws_col;
		*rows = ws.ws_row;

		return 0;
	}
}