#pragma once

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include "Terminal.h"
#include "Data.h"

namespace Input{
    void editorMoveCursor(int key);
    void editorProcessKeypress();
}