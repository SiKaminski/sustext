#pragma once
#ifndef _SUSTEXT_COLORS_H
#define _SUSTEXT_COLORS_H

/* These colors are based off ubuntu terminal colors */

enum class Highlight : int {
    normal = 0,
    comment,
    mlComment,
    keyword1,
    keyword2,
    string,
    number,
    match
};

enum class Foreground : int {
    black = 30,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    gray = 90,
    brightRed,
    brightGreen,
    brightYellow,
    brightBlue,
    brightMagenta,
    brightCyan,
    brightWhite,
};

enum class Background : int {
    black = 40,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    gray = 100,
    brightRed,
    brightGreen,
    brightYellow,
    brightBlue,
    brightMagenta,
    brightCyan,
    brightWhite,
};

#endif // _SUSTEXT_COLORS_H
