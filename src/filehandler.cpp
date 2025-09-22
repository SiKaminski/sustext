#include "filehandler.h"
// #include "utils/common.hpp"
// #include "editor.h"
// #include <errno.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

#include "utils/logger.hpp"

// int FileHandler::OpenFile(const char* filepath)
//{
//  Open a file in read mode
// eConfig.filepath = strdup(filepath);
// Editor::SelectSyntaxHighlight();
// FILE* fp = fopen(eConfig.filepath, "r");	// This line will eventually
// change

// if (fp == nullptr)
// Terminal::die((int)Severity::medium, "fopen");

// char* line = nullptr;
// size_t linecap = 0;
// ssize_t linelen = 0;

// Get the length of the line from the file
// while ((linelen = getline(&line, &linecap, fp)) != -1) {
// stop if the escape sequence for new line or return carriage is next
// while (linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] ==
// '\r')) { linelen--;
//}

// Editor::InsertRow(eConfig.numrows, line, linelen);
//}

// Deallocate memory from line and close file connection
// free(line);
// fclose(fp);
// eConfig.dirty = 0;

// return 1;
//}

// int FileHandler::SaveFile()
//{
// if (eConfig.filepath == nullptr) {
// eConfig.filepath = Editor::Prompt((char*)("Save as: %s (ESC to cancel)"),
// nullptr); if (eConfig.filepath == nullptr) { Editor::SetStatusMessage("Save
// Aborted"); return 0;
//}

// Editor::SelectSyntaxHighlight();
//}

// int len;
// char* buf = Editor::RowToString(&len);

// 644 -> give ownership of file permissions to read and write to the file,
// anyone else who didn't make the file will only be able to read it
// int fd = open(eConfig.filepath, O_RDWR | O_CREAT, 0644);
// if (fd < 0)
// error(Severity::high, "File Handler:", "Open");

// if (ftruncate(fd, len) != -1) {
// if (write(fd, buf, len) == len) {
// close(fd);
// free(buf);
// eConfig.dirty = 0;
// Editor::SetStatusMessage("[%d] bytes written to disk", len);
// return 0;
//}
//}

// close(fd);
// free(buf);
// Editor::SetStatusMessage("Unable to save File I/O error: %s",
// strerror(errno));
// return 1;
//}
