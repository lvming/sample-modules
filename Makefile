# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m := sample-cdev.o sample-misc.o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)
	PWD  := $(shell pwd)

modules clean:
	$(MAKE) -C $(KERNELDIR)/build M=$(PWD) $@

.PHONY: tags
tags:
	ctags --c++-kinds=+px -R $(KERNELDIR)/source
endif
