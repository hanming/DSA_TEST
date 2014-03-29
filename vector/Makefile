.PHONY:all clean

CC = g++

RM = rm
RMFLAGS = -fr
MKDIR = mkdir
DIR_OBJS = objs
DIR_EXES = exes
DIRS = $(DIR_OBJS) $(DIR_EXES)

EXE = $(DIR_EXES)/test.exe

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
OBJS := $(addprefix $(DIR_OBJS)/, $(OBJS))

all: $(DIRS) $(EXE)

$(DIRS) :
	$(MKDIR) $@

$(EXE):$(OBJS)
	$(CC) -o $@ $^

$(DIR_OBJS)/%.o:%.cpp
	$(CC) -o $@ -c $^

clean:
	$(RM) $(RMFLAGS) $(DIRS)