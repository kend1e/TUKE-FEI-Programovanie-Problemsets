#variables
CC=gcc
CFLAGS=-std=c11 -Werror -Wall -ggdb3
LDLIBS=-lm
OUTPUT=ps4

.PHONY: all clean

#tasks
all: $(OUTPUT)

$(OUTPUT): main.o bmp.o transformations.o
	cppcheck --check-level=exhaustive --enable=performance unusedFunction --error-exitcode=1 *c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
	
main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

transformations.o: transformations.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -rf *.o $(OUTPUT)