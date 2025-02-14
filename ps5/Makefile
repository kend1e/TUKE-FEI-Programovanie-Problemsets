#variables
CC=gcc
CFLAGS=-std=c11 -Werror -Wall -Wconversion -lm
LDLIBS=-lm
OUTPUT=ps5

.PHONY: all clean

#tasks
all: $(OUTPUT)

$(OUTPUT): main.o backpack.o command.o container.o game.o item.o parser.o room.o world.o
	cppcheck --check-level=exhaustive --enable=performance,unusedFunction --error-exitcode=1 *c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
	
main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

backpack.o: backpack.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

command.o: command.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

container.o: container.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

game.o: game.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

item.o: item.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

parser.o: parser.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

room.o: room.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

world.o: world.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -rf *.o $(OUTPUT)