CC := gcc
SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
TEST_DIR := ./test

# Exclude src/main.c from the list of source files for the library
SOURCES := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
LIBRARY := $(BUILD_DIR)/libmylib.a
EXECUTABLE := $(BUILD_DIR)/myprogram

# All test sources
TEST_SOURCES = $(wildcard test/*.c) $(wildcard test/arithmetic/*.c)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/test_%.o, $(TEST_SOURCES))
TEST_EXECUTABLE := $(BUILD_DIR)/test_program

CFLAGS := -I$(INCLUDE_DIR) -Wall -Wextra -O2
LDFLAGS := -L$(BUILD_DIR) -lmylib
TEST_LDFLAGS := -L$(BUILD_DIR) -lmylib -lcunit

all: $(LIBRARY) $(EXECUTABLE) test

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(EXECUTABLE): $(SRC_DIR)/main.c $(LIBRARY)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(LIBRARY)
	$(CC) $(CFLAGS) $^ -o $@ $(TEST_LDFLAGS)

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(OBJECTS): | $(BUILD_DIR)
$(TEST_OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

compdb:
	echo '[' > compile_commands.json
	$(foreach SRC,$(SOURCES),echo '{ "directory": "$(CURDIR)", "command": "$(CC) $(CFLAGS) -c $(SRC) -o $(BUILD_DIR)/$$(notdir $$(SRC:.c=.o))", "file": "$(SRC)" },' >> compile_commands.json;)
	sed -i '$$ s/.$$//' compile_commands.json
	echo ']' >> compile_commands.json

.PHONY: all clean run test compdb
