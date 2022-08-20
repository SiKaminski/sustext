# sustext

- [sustext](#sustext)
  - [About](#about)
  - [Pre requisites](#pre-requisites)
  - [Running the editor](#running-the-editor)
  - [Editor Commands](#editor-commands)
  - [Command Line Args](#command-line-args)
  - [Features](#features)
  - [TODO](#todo)
  
## About

Text editor made in C++ ran in the linux terminal.

The escape sequences are based off VT100 Terminals which can be clearly
seen in the source files of IO and Terminal

## Pre requisites

g++ compiler

```bash
sudo apt install g++
```

## Running the editor

To run the editor as of currently, clone the repository and run `make`

After doing so run `./sustext`

If you want to run the terminal and open a specific file you can pass it in as a parameter

Example

`./sustext <flags> [path_to_file]`

More info about different commands in the editor found in [Editor Commands](#editor-commands)

For more information about the different support commands line arguments look at [Command Line Args](#command-line-args)

## Editor Commands

`ctrl + q` -> exit the editor

`ctrl + s` -> save file

`ctrl + f` -> find string in file

## Command Line Args

`-f` -> specify file to open (might be removed because of redundancy)

`-s` -> sus mode (not implemented)

(By default the editor will open a file in write mode)

`-r` -> open file in read only mode (not implemented)

## Features

- Open files
- Basic key bindings for control
- Search through file

## TODO

- [ ] Resize the row count if the terminal window is resized (dynmaic sizing)
- [ ] different highlighting modes in viewer
- [ ] different modes of opening (viewer, editor, etc...)
- [ ] syntax highlighting??
- [ ] Console Colors
  - [ ] 3-4 bit support
  - [ ] 256 bit support
