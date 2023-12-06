CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = astar
SRC = main.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./$(TARGET)

all:
	clear
	make clean
	make
	make run