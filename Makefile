CC=gcc
CFLAGS=-Iinclude

OUT = out

# single-file examples
out/%: examples/%.c include/looseleaf.h
	mkdir -p $(OUT)
	$(CC) -o $@ examples/basic.c $(CFLAGS)

.PHONY: clean all

all: $(OUT)/basic

clean:
	rm -rf $(OUT)
