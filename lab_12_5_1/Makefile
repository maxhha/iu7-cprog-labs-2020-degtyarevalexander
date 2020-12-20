.PHONY : all debug gcov clean func unit

CC := gcc
CFLAGS := --std=gnu99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic
CFLAGS += $(cflags)
LFLAGS := -Llibs -Wl,-rpath=libs
SRCS := $(filter-out $(wildcard src/*.tmpl.c), $(wildcard src/*.c))
OBJS := $(SRCS:src/%.c=out/%.o)

STATIC_LIB := lab_07_5

UNITCFLAGS := -lcheck -lpthread -lrt $(LFLAGS) -l$(STATIC_LIB)
UNITSRCS := $(wildcard unit_tests/*.c)
UNITOBJS := $(UNITSRCS:unit_tests/%.c=out/%.o)


all : app_static.exe

app_static.exe : $(OBJS) libs/lib$(STATIC_LIB).a
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) -l$(STATIC_LIB)

debug func: CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : all

gcov :
	@rm -f out/*.c.gcov
	@echo
	@gcov -d out/*.gcda | \
		sed -u \
			-Ee "s/File ('[^']+?')/File \x1B[0;33m\1\x1B[0m/g" \
			-e "s/:([0-8]?[0-9]\.[0-9]+% of [0-9]+?)/:\x1B[0;31m\1\x1B[0m/g" \
			-e "s/:(9[0-9]+\.[0-9]+% of [0-9]+?)/:\x1B[0;32m\1\x1B[0m/g"

	@mv *.c.gcov out

func : app.exe
	@./func_tests/test.sh ./app.exe

unit : unit_tests.exe
	@./unit_tests.exe | \
		sed -u \
			-Ee "s/.+ Passed/\x1B[0;32m&\x1B[0m/g" \
			-Ee "s/.+ Assertion.+/\x1B[0;31m&\x1B[0m/g"

unit_tests.exe : $(UNITOBJS) $(filter-out out/main.o, $(OBJS)) libs/lib$(STATIC_LIB).a
	$(CC) $(CFLAGS) $(flags) -o $@ $^ $(UNITCFLAGS)

out :
	mkdir out

libs :
	mkdir libs

libs/lib$(STATIC_LIB).a: | libs
	make -C deps/lab_07_5 liblab_07_5.a
	cp deps/lab_07_5/liblab_07_5.a $@

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
	@rm -f *.exe out/*.o out/*.d out/*.gcda out/*.gcno libs/*
	make -C deps/lab_07_5 clean

-include $(SRCS:src/%.c=out/%.d)
