CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -I./include
LDFLAGS =
SRC_DIR = src
OBJ_DIR = build
BIN     = dataflow-engine

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN)
