.PHONY : build run clean

CC := gcc
CFLAGS := --std=c99 -Wall -Werror -Wpedantic

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=out/%.o)

build: app.exe

run: app.exe
	./app.exe

app.exe: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

out/%.o : ./src/%.c ./inc/%.h ./inc/log.h
	$(CC) $(CFLAGS) -o $@ -c $<

%.h :

dev:
	@make -s run
	inotifywait -e

clean:
	rm -f out/*.o
