#variables
CC=gcc
CFLAGS=-std=c11 -Werror -Wall
LDLIBS=-lm
OUTPUT=ps1

.PHONY: all tests clean

#tasks
all: $(OUTPUT)

$(OUTPUT): main.o bmp.o playfair.o
	cppcheck --check-level=exhaustive --enable=performance unusedFunction --error-exitcode=1 *c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

playfair.o: playfair.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

tests: bmp.o tests/test-reverse.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o test-reverse

clean:
	rm -rf *.o $(OUTPUT)