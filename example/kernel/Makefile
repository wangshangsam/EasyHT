obj-m := test.o
test-y = test_module.o easyht.o

MAKE = make
KDIR = /lib/modules/$(shell uname -r)/build

all:
	cp ../../include/easyht.h ./easyht.h
	cp ../../src/easyht.c ./easyht.c
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f easyht.h
	rm -f easyht.c
	$(MAKE) -C $(KDIR) M=$(PWD) clean
