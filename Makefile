CC=gcc
CFLAGS=-c -Wall -g #-std=c11
SRCS=cache.c
OBJS=cache.o
# MAKE SURE TO PUT YOUR NAME HERE
TARBALL=setzler_hw1.tar.gz

all: cache

cache:	$(OBJS)
	$(CC)  cache.o -o cache -lm

cache.o: cache.c
	$(CC) $(CFLAGS) cache.c

clean:
	/bin/rm -f cache $(OBJS) $(TARBALL)

run:
	./cache

tarball:
	tar cvzf $(TARBALL) $(SRCS) Makefile

