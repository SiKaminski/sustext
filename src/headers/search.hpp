#ifndef __SEARCH_HPP
#define __SEARCH_HPP

#include "data.hpp"
#include "editor.hpp"

void Find(EditorConfig E, const Editor& editor);
void FindCallback(char* query, int key, EditorConfig E);

#endif // __SEARCH_HPP