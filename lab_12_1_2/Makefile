.PHONY : all build run debug clean unit

all : run
run : build
	python3 runner.py

build :
	make -C deps/array libarr.so

unit :
	python3 -m unittest discover -s unit_tests
