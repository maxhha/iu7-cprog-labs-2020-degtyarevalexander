.PHONY : build run clean dev

CC := gcc
CFLAGS := --std=gnu99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic
CFLAGS += $(cflags)
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=out/%.o)

build : app.exe

run : app.exe
	./app.exe in.txt out.txt

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

out :
	mkdir out

out/%.d: ./src/%.c | ./out
	@set -e; rm -f $@; \
		$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,out/\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

out/%.o : ./src/%.c | ./out
	$(CC) $(CFLAGS) $(flags) -o $@ -c $<

clean :
	@rm -f *.exe out/*.o out/*.d out/*.gcda out/*.gcno

dev :
	@clear
	@make -s run
	@inotifywait -e close_write -mq src/ inc/ | \
		while read -r dir evts file; do clear; make -s run; done

-include $(SRCS:src/%.c=out/%.d)
