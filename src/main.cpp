#include "sustext.hpp"

int main(int argc, char** argv){
    Sustext sustext = Sustext(argc, argv);
    sustext.Initialize();

    Terminal::enableRawMode();

    if(argc >= 2){
        sustext.flags.SetFlags(argc, argv);

        //If the file does not exits the terminal just dies and closeses with
        //the exit status 'fopen'
        if(sustext.flags.Enabled(FILEIN)){
            if(!sustext.filehandler.OpenFile(sustext.flags.argout.filepath, &sustext.editor)){
                 Terminal::die("fopen");
            }
        }
    }
    
    /*
        Terminal::enableRawmode();
        sustext.editor.Init();

        if(argc >= 2){
            sustext.flags.SetFlags();

            //If the file does not exits the terminal just dies and closeses with
            //the exit status 'fopen'

            if(sustext.flags.Enabled(FILEIN)){
                if(!sustext.filemanager.OpenFile(sustext.flags.argout.filepath)){
                    sustext.terminal.die("fopen");
                }
            }
        }

        sustext.editor.SetStatusMessage("HELP: Ctrl-s = save | Ctrl-q = quit");

        while(1){
            sustext.editor.RefreshScreen();
            sustext.editor.ProcessKeypress();
        }
    */

    return 0;
}


/*
int main(int argc, char** argv){
	SusFlags sFlags = SusFlags(argc, argv);
	Terminal::enableRawMode();
	Editor::Init();

	//Check if parameters
	if(argc >= 2){
		sFlags.SetFlags();

		//If the file does not exist the terminal just dies and closes with
		//the exit code 'fopen'
		if(sFlags.Enabled(FILEIN))
			if(!Editor::OpenFile(sFlags.argout.filepath)) Terminal::die("fopen");
	}

	Editor::SetStatusMessage("HELP: Ctrl-s = save | Ctrl-q = quit");

	while(1){
		Editor::RefreshScreen();
		Editor::ProcessKeypress();
	}
	return 0;
}
*/