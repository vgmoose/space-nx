all:
	@echo "Hi! You should invoke one of the following:\n\tmake -f Makefile.pc\t# build for computer (needs gamepad)\n\tmake -f Makefile.switch\t\t# use libnx\n\tmake -f Makefile.wiiu\t\t# use wut"

clean:
	rm -rf build *.o *.nro spacenx
