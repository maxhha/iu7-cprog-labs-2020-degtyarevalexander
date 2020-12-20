.PHONY : all clean

CC := gcc
CFLAGS := --std=gnu99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic
CFLAGS += $(cflags)
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=out/%.o)

all : liblab_07_5.a

liblab_07_5.a: $(filter-out out/main.o, $(OBJS))
	ar -rc $@ $^

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

-include $(SRCS:src/%.c=out/%.d)
