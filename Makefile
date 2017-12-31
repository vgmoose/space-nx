build:
	clang *.c -lSDL2 -lm -o spacenx

debug:
	clang -g *.c -lSDL2 -lm -o spacenx

switch:
	make LLVM_POSTFIX=-5.0 LD=ld.lld-5.0 -f Makefile.switch

run:
	./spacenx

drun:
	gdb spacenx
	
clean:
	make -f Makefile.switch clean
