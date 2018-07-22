all:
	@echo "Hi! You should invoke one of the following:\n\tmake -f Makefile.pc\t# build for computer (needs gamepad)\n\tmake -f Makefile.switch\t\t# use libtransistor\n\tmake -f Makefile.libnx\t\t# use libnx"

clean:
	rm -rf build *.o *.nro spacenx
