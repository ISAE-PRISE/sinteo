# If KERNELRELEASE is defined
ifneq ($(KERNELRELEASE),)
	obj-m := user_enable_pmu.o 


# Otherwise, invoke the kernel build system
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build_xen
#        KERNELDIR ?= /usr/src/linux-headers-4.4.87-ti-xenomai-r121
	PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

endif
