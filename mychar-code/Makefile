obj-m += mychar.o
obj-m += mychar2.o
obj-m += mychar3.o
obj-m += mychar4.o
obj-m += mychar5.o
obj-m += mychar6.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

