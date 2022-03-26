# sustext

- [sustext](#sustext)
  - [About](#about)
  - [Pre requisites](#pre-requisites)
  - [Running the editor](#running-the-editor)
  - [Editor Commands](#editor-commands)
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

After doing so run `./bin/sustext`

If you want to run the terminal and open a specific file you can pass it in as a parameter

Example

`./bin/sustext [path_to_file]`

More info about different commands in the editor found in [Editor Commands](#editor-commands)

## Editor Commands

`ctrl + q` -> exit the editor

## Features

- Open files
- Basic key bindings for control

## TODO

- [ ] Add input from the user
  - [X] Simple Typing
  - [ ] Keybinds (vim like)
- [ ] Resize the row count if the terminal window is resized (dynmaic sizing)
- [ ] different highlighting modes in viewer
- [ ] different modes of opening (viewer, editor, etc...)
- [ ] syntax highlighting??
