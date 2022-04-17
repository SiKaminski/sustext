#pragma once
#ifndef __DATA_HPP
#define __DATA_HPP

typedef struct EDITOR_ROW {
	int 	idx;
	int 	size;
	int		rsize;
	char* 	chars;
	char* 	render;
	unsigned char* highlight;
	int 	hl_open_comment;
}erow;

#endif // _DATA_HPP