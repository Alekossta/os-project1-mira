CC = gcc
CFLAGS = -Wall -g
TARGET = mira
OBJ = main.o helper.o

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c
main.o: main.c helper.h 
	$(CC) $(CFLAGS) -c main.c
clean:
	rm -f $(OBJ) $(TARGET)

