CC := gcc
SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
LIBRARY := $(BUILD_DIR)/libmylib.a
EXECUTABLE := $(BUILD_DIR)/myprogram

CFLAGS := -I$(INCLUDE_DIR) -Wall -Wextra -O2

all: $(LIBRARY) $(EXECUTABLE)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(SRC_DIR)/main.c $(LIBRARY)
	$(CC) $(CFLAGS) $< -o $@ -L$(BUILD_DIR) -lmylib

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

compdb:
	echo '[' > compile_commands.json
	$(foreach SRC,$(SOURCES),echo '{ "directory": "$(CURDIR)", "command": "$(CC) $(CFLAGS) -c $(SRC) -o $(BUILD_DIR)/$$(notdir $$(SRC:.c=.o))", "file": "$(SRC)" },' >> compile_commands.json;)
	sed -i '$$ s/.$$//' compile_commands.json
	echo ']' >> compile_commands.json

.PHONY: all clean run compdb

