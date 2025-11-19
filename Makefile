SOURCES = src/main.c src/board.c src/player.c src/bot.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -fopenmp -Wall -Wno-char-subscripts -c
LFLAGS = -fopenmp -o
OUTPUT = main.out

$(OUTPUT): $(OBJECTS)
	$(CC) $(LFLAGS) $@ $^

src/%.o : src/%.c
	$(CC) $(CFLAGS) $< -o $@
	@echo "Compilation of $< done..."

.PHONY: clean

clean:
	@rm -rf $(OBJECTS) $(OUTPUT)
