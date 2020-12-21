.PHONY : all build run debug clean

all : run
run : build
	python3 runner.py

build :
	make -C deps/array libarr.so
