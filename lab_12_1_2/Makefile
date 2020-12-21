.PHONY : all build run debug clean unit

all : run
run : build
	python3 src

build :
	make -C deps/array libarr.so

unit :
	python3 -m unittest discover -s unit_tests

clean :
	rm -rf $(wildcard ./*/__pycache__/)
	make -C deps/array clean
