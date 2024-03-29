# Debug mode (comment this line to build project in release mode)
DEBUG = false

# Compiler
CC = g++
# Command used to remove files
RM = -rm -f
# Compiler and pre-processor options
CPPFLAGS = -Wall -std=c++17 -O1 -lLLVM-14 -Wno-return-type
# Add -Ofast for opt
# Debug flags
DEBUGFLAGS = -g
# Resulting program file name
EXE_NAME = zigcc
# The source file extentions
SRC_EXT = cpp
# The header file types
HDR_EXT = h

# Source directory
SRCDIR = src
# Headers directory
INCDIR = include
# Main output directory
OUTPUT_DIR = bin
# Release output directory
RELEASEDIR = release
# Debug output directory
DEBUGDIR = debug
# Dependency files directory
DEPDIR = dep
# Libraries (defines different library path if '.MAC' file is found in directory)
LIBS = -L./antlr4/dist/ -l:libantlr4-runtime.so.4.12.0 -lLLVM-14
# List of include paths
INCLUDES = -I ./$(INCDIR) -I ./antlr4/include -I /usr/lib/llvm-14/include

ifdef DEBUG
BUILD_PATH = ./$(OUTPUT_DIR)/$(DEBUGDIR)
else
DEBUGFLAGS =
BUILD_PATH = ./$(OUTPUT_DIR)/$(RELEASEDIR)
endif
# Source directory path
SRC_PATH = ./$(SRCDIR)
# Dependencies path
DEP_PATH = $(BUILD_PATH)/$(DEPDIR)

# List of source files
SOURCES = $(wildcard $(SRC_PATH)/*.$(SRC_EXT)) $(wildcard $(SRC_PATH)/**/*.$(SRC_EXT))
# List of object files
OBJS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# List of dependency files
DEPS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(DEP_PATH)/%.d)
# Source directories (VPATH is internally used by make)
VPATH := $(dir $(SOURCES))

.PHONY: all clean compile_grammar rebuild help

all: $(BUILD_PATH)/$(EXE_NAME)

clean:
	@$(RM) $(BUILD_PATH) -r
	@$(RM) ./include/antlr -r
	@$(RM) ./src/antlr -r

compile_grammar:
	./compile_grammar.sh

rebuild: clean compile_grammar all

rebuild_nogrammar : clean all

help:
	@echo '				### MAKEFILE HELP ###'
	@echo 'PHONY TARGETS:'
	@echo '	all 	...'
	@echo '	clean 	...'
	@echo '	rebuild ...'
	@echo '	compile_grammar	...'
	@echo '	help	...'

# Build object files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@mkdir -p $(dir $(DEPS)) $(dir $(OBJS))
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) $(INCLUDES) -MMD -MP -MF $(DEP_PATH)/$*.d -c $< -o $@

# Build main target
$(BUILD_PATH)/$(EXE_NAME): $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_PATH)/$(EXE_NAME) $(LIBS) $(DEBUGFLAGS)
