TARGET = raid
SRCS = $(wildcard *.c)

FLAGS=-O2 -Wall -g
INCLUDE=-I. -I../../include
LIBDIR=-L../../lib
LIBS=-lgalileo2 -lm


CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

TESTLD=$(LIBDIR) -lm

all: $(SRCS:.c=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

test: $(SRCS:.c=.o)
	gcc -o $@ $^ $(TESTLD)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
