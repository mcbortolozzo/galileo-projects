TARGET		= stx srcv
SRCS= string-tx.c string-rcv.c

FLAGS=-O2 -Wall -g
INCLUDE=-I. -I../../include
LIBDIR=-L../../lib
LIBS=-lgalileo2 -lm

CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

stx: string-tx.o
	$(CC) -o $@ $^ $(LDFLAGS)

srcv: string-rcv.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
