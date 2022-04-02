#pragma once

#include "defines.hpp"

typedef struct erow{
	int 	size;
	int		rsize;
	char* 	chars;
	char* 	render;
	unsigned char* highlight;
}erow;