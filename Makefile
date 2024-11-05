# Set Linux macros
platform := Linux
CXX ?= g++
linkFlags += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

THEN := ;
PATHSEP := /
MKDIR := mkdir -p
RM := rm -rf

# Set build directories and target files
buildDir := bin
executable := app
target := $(buildDir)/$(executable)

sources := $(wildcard src/**/*.cpp src/*.cpp)
objects := $(patsubst src/%, $(buildDir)/%, $(patsubst %.cpp, %.o, $(sources)))

# Compilation flags
compileFlags := -std=c++17 -I include

# Default target: create bin directory, compile, and execute
all: $(buildDir) $(target)
	@$(target) # Run the executable after building

# Create bin directory if it doesn't exist
$(buildDir):
	$(MKDIR) $(buildDir)

# Link the program and create the executable
$(target): $(objects)
	$(CXX) $(objects) -o $(target) $(linkFlags)

# Compile objects to the build directory
$(buildDir)/%.o: src/%.cpp Makefile
	$(MKDIR) $(@D)
	$(CXX) -MMD -MP -c $(compileFlags) $< -o $@

# Run the executable
execute: $(target)
	$(target) $(ARGS)

# Clean up all relevant files
clean:
	$(RM) $(buildDir)/*

# Include dependency files for tracking header changes
-include $(objects:.o=.d)
