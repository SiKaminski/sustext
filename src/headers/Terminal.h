#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
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