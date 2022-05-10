#pragma once
#ifndef _SUSTEXT_GLOBALS_H
#define _SUSTEXT_GLOBALS_H

#include "editor.h"
#include "terminal.h"
#include <stdint.h>

#define SUSTEXT_VERSION "v1.2.6"

extern uint64_t Flags;
extern Editor::ConfigData eConfig;
extern Terminal::ConfigData tConfig;

#endif // _SUSTEXT_GLOBALS_H