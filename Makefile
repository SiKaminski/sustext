OBJ = sus
OBJSFILES = $(wildcard src/*.cpp)
CPP = gcc
CPPFLAGS = -Wall -Wextra -pedantic
HEADERS = src/headers


$(OBJ): $(OBJSFILES)
	$(CPP) $^ -o $@  $(CPPFLAGS) -I$(HEADERS)
clean: $(OBJ)
	rm $(OBJ)

# sustext: sustext.c
# 	$(CC) sustext.c -o sustext -Wall -Wextra -pedantic -std=c99
# 	./sustext
# clean: sustext
# 	rm $^
