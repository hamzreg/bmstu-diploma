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

distclean:
	@rm -f *.ko *.symvers *.mod

load:
	sudo insmod $(TARGET).ko

info:
	sudo lsmod | grep $(TARGET)

log:
	sudo dmesg | grep $(TARGET)

unload:
	sudo rmmod $(TARGET).ko


add-disk:
	cat /sys/class/zram-control/hot_add

get-comp-algorithm:
	cat /sys/block/zram$(id)/comp_algorithm

set-comp-algorithm:
	echo $(algorithm) > /sys/block/zram$(id)/comp_algorithm

set-disksize:
	echo $(disksize) > /sys/block/zram$(id)/disksize

memory-stat:
	cat  /sys/block/zram$(id)/mm_stat

reset-disk:
	echo 1 > /sys/block/zram$(id)/reset

remove-disk:
	echo $(id) > /sys/class/zram-control/hot_remove
