CC = gcc
CFLAGS = -march=native -fPIC -Wall -Wshadow -g -O0
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
TARGETS = allocator.so demo statichooks.so

all: $(TARGETS)

%.so: %.o utils.o
	$(CC) $(CFLAGS) -shared -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGETS)
