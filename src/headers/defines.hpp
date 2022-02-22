#ifndef __DEFINES_H
#define __DEFINES_H

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)
#define SUSTEXT_VERSION "0.0.1"

#endif // __DEFINES_H