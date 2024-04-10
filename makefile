COMPILER = gcc
FLAGS = -o
NAME = floppysolver
MAIN = ./src/main.c

test:
	make clean
	clear
	make compile
	./floppysolver

compile: $(MAIN)
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a src/main.c -I raylib -o floppysolver

clean:
	rm -f floppysolver
	rm -rf floppysolver.dSYM


time: 
	make compile
	time ./floppysolver

