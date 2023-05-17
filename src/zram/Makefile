# SPDX-License-Identifier: GPL-2.0-only
# zram-y	:=	zcomp.o zram_drv.o

# obj-$(CONFIG_ZRAM)	+=	zram.o

KERNEL_VERSION = $(shell uname -r)

OBJS = zcomp.o zram_drv.o
TARGET = zram

obj-m := $(TARGET).o
$(TARGET)-objs := $(OBJS)

all:
	$(MAKE) -C /lib/modules/$(KERNEL_VERSION)/build M=$(PWD) modules

$(TARGET).o: $(OBJS)
	$(LD) -r -o $@ $(OBJS)

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions

disclean: clean
	@rm -f *.ko *.symvers *.mod# SPDX-License-Identifier: GPL-2.0-only
