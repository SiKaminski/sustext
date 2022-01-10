#ifndef MACROS_H
#define MACROS_H

#define CTRL_KEY(k) ((k) & 0x1f)
#define SUSTEXT_VERSION "0.0.1"

enum editorKey{
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

#endif // MACROS_H