obj-m += IO-Management.o Hello.o

KDIR = /usr/src/linux-headers-4.8.0-22-generic
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order
