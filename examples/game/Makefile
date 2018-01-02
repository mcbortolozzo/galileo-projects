TARGET = raid
SRCS = $(wildcard *.c)

FLAGS=-O2 -Wall -g
INCLUDE=-I. -I../../include
LIBDIR=-L../../lib
LIBS=-lgalileo2 -lm

ifeq ($(galileo), 1)
	GALILEO := -DGALILEO
endif

CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

TESTLD=$(LIBDIR) -lm

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

test: $(SRCS:.c=.o)
	gcc -o $@ $^ $(TESTLD)

%.o: %.c
	$(CC) $(GALILEO) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
