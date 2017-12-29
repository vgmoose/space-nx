build:
	clang *.c -lSDL2 -o spacenx
	
debug:
	clang -g *.c -lSDL2 -o spacenx
	
	
switch:
ifeq ($(strip $(LIBTRANSISTOR_HOME)),)
	$(error "Please set LIBTRANSISTOR_HOME in your environment. export LIBTRANSISTOR_HOME=<path to libtransistor>")
endif
	
	include $(LIBTRANSISTOR_HOME)/libtransistor.mk

	%.o: %.c
		$(CC) $(CC_FLAGS) -Wno-pointer-arith -c -o $@ $<

	%.o: %.S
		$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

	$(PROGRAM).nro.so: ${OBJ} $(LIBTRANSITOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
		$(LD) $(LD_FLAGS) -o $@ ${OBJ} $(LIBTRANSISTOR_NRO_LDFLAGS)

run:
	./spacenx

drun:
	gdb spacenx