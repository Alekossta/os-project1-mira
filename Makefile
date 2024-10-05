CC = gcc
CFLAGS = -Wall -g
TARGET = bin/miris
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Automatically detect all .c files in src folder
SRC = $(wildcard $(SRC_DIR)/*.c)

# Convert .c files to corresponding .o files in obj folder
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Target rule to build the final executable
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule for compiling .c files into .o files (for files that have .h)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Special rule for compiling main.c (no .h file)
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
run:
	make $(TARGET)
	clear
	./$(TARGET)
