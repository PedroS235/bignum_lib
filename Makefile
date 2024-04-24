.PHONY: all setup run test clean

# Default build directory
BUILD_DIR := build

# Build type (Release, Debug, etc)
BUILD_TYPE ?= Release

# Default target executed when no arguments are given to make.
default: run

# Setup the build system with CMake
setup: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..

# Target to build the project
all: setup
	cd $(BUILD_DIR) && $(MAKE)

# Target to run the main executable
run: all
	./$(BUILD_DIR)/bignum

# Target to run tests
test: all
	./$(BUILD_DIR)/bignum_test

# Clean up build directory
clean:
	rm -rf $(BUILD_DIR)

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

