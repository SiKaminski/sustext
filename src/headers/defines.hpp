#pragma once

/* Compatability check for different platforms */
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif // _DEFAULT_SOURCE

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif // _BSD_SOURCE

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <time.h>
#include <stdarg.h>
#include <fcntl.h>

#define CTRL_KEY(k) ((k) & 0x1f)
#define SUSTEXT_VERSION "v1.2.5"
#define SUSTEXT_TAB_STOP 8
#define SUSTEXT_QUIT_TIMES 1

#define FLAGS_INIT {false, false}
#define ARGS_INIT {nullptr}

typedef u_int64_t uint64_t;

enum editorKey{
	BACKSPACE = 127,
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	PAGE_UP,
	PAGE_DOWN
};

enum editorHighlight{
	HL_NORMAL = 0,
	HL_NUMBER,
	HL_MATCH
};