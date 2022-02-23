#File Directory things (might be overkill idk yet)
INCLUDE = -I
BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = obj
LD = LD
LDFLAGS = 

dir_guard=@mkdir -p $(@D)

#Compiler and linker things
CC = g++
CCFLAGS = -c -g -Wall -Wextra -pedantic $(INCLUDE) 

#Essential files and groups
OBJ = $(addprefix $(BIN_DIR)/, sustext)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

run: all
	@echo
	@./$(OBJ)

all: $(OBJ) 
	$(dir_guard)
	@echo ---- Generating $^ ---

$(OBJ): $(OBJS)
	$(dir_guard)
	@echo ---- Linking $^ ----
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(dir_guard)
	@echo ---- Compiling $^ ----
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/
	rm -rf $(OBJ_DIR)/
