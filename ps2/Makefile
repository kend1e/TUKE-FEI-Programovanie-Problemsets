#variables
CC=gcc
CFLAGS=-std=c11 -Werror -Wall
LDLIBS=-lcurses
OUTPUT=ps2

.PHONY: all clean

#tasks
all: $(OUTPUT)

$(OUTPUT): main.o hof.o k.o ui.o
	cppcheck --check-level=exhaustive --enable=performance unusedFunction --error-exitcode=1 *c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

hof.o: hof.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

k.o: k.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

ui.o: ui.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -rf *.o $(OUTPUT)