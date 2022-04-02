#include "filehandler.hpp"

FileHandler::FileHandler(){}
FileHandler::~FileHandler(){}

int FileHandler::OpenFile(char* filepath, Editor* editor){
    //Open a file in read mode
	free(editor->E.filepath);
	editor->E.filepath = strdup(filepath);
	editor->SelectSyntaxHighlight();
	FILE* fp = fopen(editor->E.filepath, "r"); 		// This line will eventually change
	if(!fp) Terminal::die("fopen");

	char* line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	//Get the length of the line from the file
	while((linelen = getline(&line, &linecap, fp)) != -1){
		//stop if the escape sequence for new line or return carriage is next
		while(linelen > 0 && (line[linelen - 1] == '\n' ||
		line[linelen - 1] == '\r'))
			linelen--;
		editor->InsertRow(editor->E.numrows, line, linelen);
	}
	//Deallocate memory from line and close file connection
	free(line);
	fclose(fp);
	editor->E.dirty = 0;

	return 1;
}

int FileHandler::SaveFile(Editor* editor){
   	if(editor->E.filepath == NULL){
		editor->E.filepath = editor->Prompt((char*)"Save as: %s (ESC to cancel)", NULL);
		if(editor->E.filepath == NULL){
			editor->SetStatusMessage("Save Aborted");
			return 0;
		}
		editor->SelectSyntaxHighlight();
	}

	int len;
    char* buf = editor->RowToString(&len);

    // 644 -> give ownership of file permissions to read and write to the file, anyone else who didn't make
    // the file will only be able to read it
	int fd = open(editor->E.filepath, O_RDWR | O_CREAT, 0644);
    if(fd != -1){
		if(ftruncate(fd, len) != -1){
   			if(write(fd, buf, len) == len){
 	  		 	close(fd);
 	  		 	free(buf);
				editor->E.dirty = 0;
				editor->SetStatusMessage("[%d] bytes written to disk", len);
				return 0;
			}
		}
		close(fd);
	}
	free(buf);
	editor->SetStatusMessage("Unable to save File I/O error: %s", strerror(errno));
    return 1;
}