.PHONY : all debug clean

CC := gcc
CFLAGS := --std=gnu99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic
CFLAGS += $(cflags)
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=out/%.o)

all : libarr.so

libarr.so : CFLAGS += -fPIC
libarr.so : $(OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $^ -lm

debug func: CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : all

out :
	mkdir out

out/%.d: ./src/%.c | ./out
	@set -e; rm -f $@; \
		$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,out/\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

out/check_%.o : unit_tests/check_%.c | ./out
	$(CC) $(CFLAGS) $(flags) -o $@ -c $<

out/%.o : ./src/%.c | ./out
	$(CC) $(CFLAGS) $(flags) -o $@ -c $<

clean :
	@rm -f *.exe out/*.o out/*.d out/*.gcda out/*.gcno ./*.so

-include $(SRCS:src/%.c=out/%.d)
