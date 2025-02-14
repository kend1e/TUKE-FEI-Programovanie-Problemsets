#variables
CC=gcc
CFLAGS=-std=c11 -Werror -Wall
LDLIBS=-lm

#tasks
cheesefactory: cheesefactory.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

mm: mm.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

isolation: isolation.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

racer: racer.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -rf cheesefactory mm isolation racer