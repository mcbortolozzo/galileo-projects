TARGET = lcdbutton lcdservo

FLAGS=-O2 -Wall -g
INCLUDE=-I. -I../../include
LIBDIR=-L../../lib
LIBS=-lgalileo2 -lm

CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

lcdbutton: lcdbutton.o
	$(CC) -o $@ $^ $(LDFLAGS)

lcdservo: lcd-servo.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
