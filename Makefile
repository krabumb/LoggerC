# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Iinclude

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE_DIR := include

# Targets
EXEC := $(BIN_DIR)/loggerC
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default make
all: $(EXEC)

# Linking
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@

# Object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

# Cleaning up
clean:
	rm -rf $(BUILD_DIR)

# Non-file targets
.PHONY: all clean
