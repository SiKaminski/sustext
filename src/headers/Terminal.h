#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdlib.h>
#include "Data.h"
#include "Macros.h"

namespace Terminal{
	void die(const char* s);
	void disableRawMode();
	void enableRawMode();
	int editorReadKey();
	int getCursorPosition(int *rows, int *cols);
	int getWindowSize(int *rows, int *cols);
}

#endif // TERMINAL_H