obj-m += helloword.o wait_queue.o my_timer.o
##obj-m += wait_queue.0

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all default: modules
install:  modules_install

modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@

