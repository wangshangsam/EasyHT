CC 		= gcc
CFLAGS 	= -g -c
LDFLAGS = 

TARGET 	= test
OBJS	= easyht.o test.o


all: $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f easyht.h easyht.c

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $? -o $@

%.o: %.c
	$(CC) $(CFLAGS) $? -o $@

easyht.c:
	cp ../../include/easyht.h ./easyht.h
	cp ../../src/easyht.c ./easyht.c
