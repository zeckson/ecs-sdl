# Project Name
PROJECT_NAME = ECS

SRC_DIR = src
BUILD_DIR = build
CC = g++

# Find all .cpp files recursively in the src directory
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

SDL_LIBRARY_FLAGS = $(shell pkg-config SDL2 --cflags)

SDL_CORE_LIBRARY = $(shell pkg-config SDL2 --libs)
SDL_IMAGE_LIBRARY = $(shell pkg-config SDL2_image --libs)
SDL_TTF_LIBRARY = $(shell pkg-config SDL2_ttf --libs)

# SDL2 library configuration
SDL_LIBRARY = $(SDL_CORE_LIBRARY) $(SDL_IMAGE_LIBRARY) $(SDL_TTF_LIBRARY) $(SDL_LIBRARY_FLAGS)

# Compiler flags
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g -mmacosx-version-min=13.0

CXXFLAGS = $(COMPILER_FLAGS) $(SDL_LIBRARY)

.PHONY: compile clean run all

# Build rule for the executable
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $(BUILD_DIR)/$@

compile: $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $(BUILD_DIR)/$(PROJECT_NAME)

# Create the build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: compile
	$(BUILD_DIR)/${PROJECT_NAME}

all: compile
