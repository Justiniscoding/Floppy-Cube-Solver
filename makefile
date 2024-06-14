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
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a src/main.c src/floppy.c src/helpers.c src/moves.c -I raylib -o floppysolver

clean:
	rm -f floppysolver
	rm -rf floppysolver.dSYM

linkerCheck:
	clear
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a src/main.c -I raylib -o floppysolver -v

time: 
	make compile
	time ./floppysolver

macBuild:
	make compile
	rm -rf floppysolver.app

	mkdir floppysolver.app
	mkdir floppysolver.app/Contents
	mkdir floppysolver.app/Contents/MacOS
	mkdir floppysolver.app/Contents/Resources
	touch floppysolver.app/Contents/Info.plist

	mv floppysolver floppysolver.app/Contents/MacOS

	echo "<?xml version="1.0" encoding="UTF-8"?> <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd"> <plist version="1.0"> <dict> <key>CFBundleExecutable</key> <string>my_app</string> </dict> </plist>" >> floppysolver.app/Contents/Info.plist


