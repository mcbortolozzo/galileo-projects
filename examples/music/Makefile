TARGETS		= ode light fluorescent

FLAGS=-O2 -Wall -g
INCLUDE=-I. -I../../include
LIBDIR=-L../../lib
LIBS=-lgalileo2 -lm

#CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGETS)

ode: ode.o
	$(CC) -o $@ $^ $(LDFLAGS)

light: light.o
	$(CC) -o $@ $^ $(LDFLAGS)

fluorescent: fluorescent.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGETS)
