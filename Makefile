CPP = gcc 
LD = ld
LDFLAGS = #Undecided Linker flags
CPPFLAGS = -Wall -Wextra -pedantic
HEADERS = src/headers

OBJ = sus
SRCDIR = src
OBJDIR = lib
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)      
CXX_SOURCES := $(wildcard $(SRCDIR)/*.cpp)
CXX_OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

$(CXX_OBJS): link

$(CXX_OBJS): $(CXX_SOURCES)
	@echo -- COMPILING --
	$(CPP) $(CPPFLAGS) -I$(HEADERS) -c $^ -o $@ 
link:
	@echo -- LINKING --
	$(LD) $^ -o $@ $(CXX_OBJS)
clean:
	rm $(OBJDIR)/* -rf
	rm $(OBJ)

# sustext: sustext.c
# 	$(CC) sustext.c -o sustext -Wall -Wextra -pedantic -std=c99
# 	./sustext
# clean: sustext
# 	rm $^
