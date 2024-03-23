# Project Name
PROJECT_NAME := ECS

SRC_DIR := src
BUILD_DIR := build
CC := g++

# Generate list of source files for each directory
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

SDL_LIBRARY_FLAGS := $(shell pkg-config SDL2 --cflags)

SDL_CORE_LIBRARY := $(shell pkg-config SDL2 --libs)
SDL_IMAGE_LIBRARY := $(shell pkg-config SDL2_image --libs)
SDL_TTF_LIBRARY := $(shell pkg-config SDL2_ttf --libs)

# SDL2 library configuration
SDL_LIBRARY := $(SDL_CORE_LIBRARY) $(SDL_IMAGE_LIBRARY) $(SDL_TTF_LIBRARY)

# Compiler flags
COMPILER_FLAGS := -std=c++17 -Wall -O0 -g -mmacosx-version-min=14.0 $(SDL_LIBRARY_FLAGS)

CXXFLAGS = $(COMPILER_FLAGS)

.PHONY: clean run all echo compile recompile

# Debugging echo rule
echo:
	@echo "Sources: " $(SRCS)
	@echo "Objects: " $(OBJS)

# Create the build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule for object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling: " $< " into: " $@
	mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -DPROJECT_NAME='"$(PROJECT_NAME)"' -c $< -o $@

# Build rule for the executable
compile: $(OBJS)
	$(CC) $(CXXFLAGS) $(SDL_LIBRARY) $^ -o $(BUILD_DIR)/$(PROJECT_NAME)

clean:
	rm -rf $(BUILD_DIR)

recompile: clean compile

run: compile
	$(BUILD_DIR)/${PROJECT_NAME}

all: compile
