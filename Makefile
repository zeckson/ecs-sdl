PROJECT_NAME := ECSSDL2
PROFILE_DEBUG := debug
PROFILE_RELEASE := release

PROFILE_CURRENT = $(PROFILE_DEBUG)

BUILD_ROOT = build
BUILD_DIR = $(BUILD_ROOT)/$(PROFILE_CURRENT)

.PHONY: clean run all echo compile recompile install

# Debugging echo rule
echo:
	@echo "Run \`make all\` to build project $(PROJECT_NAME) with profile $(PROFILE_CURRENT)"

# Create the build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Install cmake project
install: $(BUILD_DIR)
	cmake -DCMAKE_BUILD_TYPE=$(PROFILE_CURRENT) -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B $(BUILD_DIR)

# Build rule for the executable
compile: install
	@echo "Configuring and building project..."
	cmake --build $(BUILD_DIR) --target $(PROJECT_NAME) -j 6 -v

clean:
	@echo "Cleaning build directory..."
	cmake --build $(BUILD_DIR) --target clean -j 6

test:
	@echo "Running tests..."
	cd $(BUILD_DIR) && ctest

recompile: clean compile

run: compile
	@echo "Running the project..."
	$(BUILD_DIR)/${PROJECT_NAME}

all: compile
