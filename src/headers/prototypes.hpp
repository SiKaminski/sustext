#pragma once

#include "data.hpp"
#include "configs.hpp"

// Editor Prototypes
int RowCxToRx(erow* row, int rx);
int RowRxToCx(erow* row, int rx);
void FindCallBack(char* query, int key, EditorConfig* E);

// Terminal Protopytes

//Syntax Highlighting
int isSeperator(int c);
void SelectSyntaxHighlight();