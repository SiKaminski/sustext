#pragma once
#ifndef _PROTOTYPES_H
#define _PROTOTYPES_H

// #include "data.h"
// #include "configs.h"
#include "editor.h"

// Editor Prototypes
int RowCxToRx(Editor::RowData* row, int rx);
int RowRxToCx(Editor::RowData* row, int rx);
void FindCallBack(char* query, int key, Editor::ConfigData* E);

// Terminal Protopytes

//Syntax Highlighting
int isSeperator(int c);
void SelectSyntaxHighlight();

#endif // __PROTOTYPES_H