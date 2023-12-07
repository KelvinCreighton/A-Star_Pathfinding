CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = astar
SRC = main.c map.c
OBJ = $(SRC:.c=.o)
DEP = map.h

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
	
clear:
	clear

run:
	./$(TARGET)

all: clear clean $(TARGET) run