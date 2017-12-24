DIRS 		= examples/music examples/lcd
LIBDIRS = lib


FLAGS=-O2 -Wall -g -MMD
INCLUDE=-I. -I../include
LIBDIR=-L../lib
LIBS=-lgalileo2 -lm

#CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(DIRS)

$(DIRS): $(LIBDIRS) force_look
	$(MAKE) -C $@

$(LIBDIRS): force_look
	$(MAKE) -C $@

force_look:
	true

clean:
	$(MAKE) -C examples/music clean
	$(MAKE) -C examples/lcd clean
	$(MAKE) -C lib clean


distclean: clean
	$(MAKE) -C examples/music distclean
	$(MAKE) -C examples/lcd distclean
	$(MAKE) -C lib distclean
