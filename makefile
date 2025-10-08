CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -g

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

TARGET = $(BIN_DIR)/myhttpd

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR): 
	mkdir -p $@
$(BIN_DIR):
	mkdir -p $@

clean: 
	rm -fr $(OBJ_DIR) $(BIN_DIR)
