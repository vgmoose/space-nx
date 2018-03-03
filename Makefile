all:
	@echo "Hi! You should invoke one of the following:\n\tmake -f Makefile.pc\t\t# build for computer (SDL1)\n\tmake -f Makefile.pc sdl2\t# build for computer (SDL2)\n\tmake -f Makefile.switch\t\t# use libtransistor\n\tmake -f Makefile.nx\t\t# use libnx"

clean:
	rm -rf build *.o *.nro spacenx
