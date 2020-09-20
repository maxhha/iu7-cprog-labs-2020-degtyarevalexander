.PHONY : all run debug runmem gcov clean func check   unit

CC := gcc
CFLAGS := --std=c99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic
OUTDIR := ./out
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=$(OUTDIR)/%.o)

CODECHECKERDIR := ../../CodeChecker/CodeChecker
CODECHECKER := $(CODECHECKERDIR)/CodeChecker.exe --rules $(CODECHECKERDIR)/Rules.txt

all : app.exe

run : app.exe
	./app.exe $(args)

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o : src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

debug : CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : all

runmem : debug
	drmemory -- ./app.exe $(args)

gcov : $(OBJS:.o=.gcda)
	@rm -f $(OUTDIR)/*.c.gcov
	@gcov -d $^
	@mv *.c.gcov $(OUTDIR)

func : app.exe
	@./func_tests/test.sh ./app.exe

clean :
	@rm -f *.exe $(OUTDIR)/*.o $(OUTDIR)/*.gcda $(OUTDIR)/*.gcno

check : SHELL:=/usr/bin/bash
check :
	$(CODECHECKER) $(SRCS)
