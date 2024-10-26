CC = gcc
CFLAGS = -Wall -g
TARGET = bin/miris
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
run:
	make $(TARGET)
	clear
	./$(TARGET) -i input/files/data1000-25.txt -o output/defaultOutput.txt

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(MAKE) run