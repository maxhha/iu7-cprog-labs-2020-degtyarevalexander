.PHONY : all run debug prep runmem gcov clean   unit func

CC := gcc
CFLAGS := --std=c99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic
OUTDIR := ./out
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=$(OUTDIR)/%.o)

all : prep app.exe

run : all
	./app.exe

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o : src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

debug : CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : all

runmem: debug
	drmemory -- ./app.exe

gcov: $(OBJS:.o=.gcda)
	@rm -f $(OUTDIR)/*.c.gcov
	@gcov -d $^
	@mv *.c.gcov $(OUTDIR)

clean :
	@rm -f *.exe $(OUTDIR)/*.o $(OUTDIR)/*.gcda $(OUTDIR)/*.gcno

prep :
	@mkdir -p $(OUTDIR)
