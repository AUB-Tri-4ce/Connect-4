SOURCES = src/main.c src/board.c src/player.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -c
LFLAGS = -o
OUTPUT = main.out

$(OUTPUT): $(OBJECTS)
	$(CC) $(LFLAGS) $@ $^

.c.o:
	$(CC) $(CFLAGS) $<
	@echo "Compilation of $< done..."

.PHONY: clean

clean:
	@rm -rf *.o $(OUTPUT)
