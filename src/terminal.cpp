//#include "terminal.h"

//#include <ctype.h>
//#include <errno.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/ioctl.h>
//#include <unistd.h>
//#include <termios.h>
//#include <sys/types.h>
//#include <time.h>
//#include <stdarg.h>
//#include <fcntl.h>

//#include "Debug/logger.h"
//#include "common.h"

//void Initialize()
//{


//}

//void Terminal::die(const int severity, const char* s)
//{
	//Clear screen on exit
	//write(STDOUT_FILENO, "\x1b[2J", 4);
	//write(STDOUT_FILENO, "\x1b[H", 3);
    //error(Severity::unknown, "Terminal Die:", s);
//}

//void Terminal::DisableRawMode()
//{
	//Set the attributes of the terminal back to its origional state
	//if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tConfig.OrigTermios) == -1)
		//die((int)Severity::high, "tcsetattr");

	//system("clear");
//}

//void Terminal::EnableRawMode()
//{
    //LOG_INFO << "Enabling terminal raw mode" << std::endl;
	//Store original termios attribs, if there is an error disable raw mode and exit
	//if (tcgetattr(STDIN_FILENO, &tConfig.OrigTermios) == -1)
		//die((int)Severity::high, "tcgetattr");

	//atexit(DisableRawMode);

	//Define a new terminal
	//termios raw = tConfig.OrigTermios;

	//Disable flags to leave canonical mode
	//raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	//raw.c_oflag &= ~(OPOST);
	//raw.c_cflag |= (CS8);
	//raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	//raw.c_cc[VMIN] = 0;
	//raw.c_cc[VTIME] = 1;

	//Set the new terminal
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	//if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		//die((int)Severity::high, "tcsetattr");

    //LOG_SUCCESS << "Enabled terminal raw mode" << std::endl;
//}

//Editor::Key Terminal::EditorReadKey()
//{
	//using namespace Editor;
	//int nread;
	//char c;

	//while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		//if (nread == -1 && errno != EAGAIN) 
			//die((int)Severity::medium, "read");
	//}

	//Check for escape sequence
	//if (c == '\x1b') {
		//Get a 3 byte buffer for the escape code
		//char seq[3];

		//if (read(STDIN_FILENO, &seq[0], 1) != 1)
			//return Key::escapeSequence;

		//if (read(STDIN_FILENO, &seq[1], 1) != 1)
			//return Key::escapeSequence;

		//'27'
		//if (seq[0] == '[') {
			//if (seq[1] >= '0' && seq[1] <= '9') {
				//if (read(STDOUT_FILENO, &seq[2], 1) != 1)
					//return Key::escapeSequence;

				//if (seq[2] == '~') {
					//switch (seq[1]) {
                        //case '1':
                            //return Key::home;
                        //case '3':
                            //return Key::del;
                        //case '2':
                            //return Key::end;
                        //case '5':
                            //return Key::pageUp;
                        //case '6':
                            //return Key::pageDown;
                        //case '7':
                            //return Key::home;
                        //case '8':
                            //return Key::end;
					//}
				//}
			//} else {
				//There has to be a better way of implementing keypresses right?
				//switch (seq[1]) {
                    //case 'A':
                        //return Key::arrowUp;
                    //case 'B':
                        //return Key::arrowDown;
                    //case 'C':
                        //return Key::arrowRight;
                    //case 'D':
                        //return Key::arrowLeft;
                    //case 'H':
                        //return Key::home;
                    //case 'F':
                        //return Key::end;
				//}
			//}
		//} else if (seq[0] == 'O') {
			//switch (seq[1]) {
                //case 'H':
                    //return Key::home;
                //case 'F':
                    //return Key::end;
			//}
		//}

		//return Key::escapeSequence;
	//} else {	
		//return (Key)c;
	//}
//}

//int Terminal::GetCursorPosition(int* rows, int* cols)
//{
	//char buf[32];
	//unsigned int i = 0;

	//Failed to provide a position
	//if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
		//return -1;

	//while (i < sizeof(buf) - 1) {
		//if (read(STDIN_FILENO, &buf[i], 1) != 1)
			//break;

		//if (buf[i] == 'R')
			//break;

		//i++;
	//}

	//buf[i] = '\0';
	
	//What the escape sequence doin?
	//if (buf[0] != '\x1b' || buf[1] != '[')
		//return -1;

	//If &buf[2] does not have the screen size then zad :(
	//if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
		//return -1;

	//return 0;
//}

//int Terminal::GetWindowSize(int* rows, int* cols)
//{
	//winsize ws;

	//if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
		//Make sure the curusor reaches the bottom right of the screen
		//if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
			//return -1;

		//return GetCursorPosition(rows, cols);
	//} else {
		//*cols = ws.ws_col;
		//*rows = ws.ws_row;
		//return 0;
	//}
//}
