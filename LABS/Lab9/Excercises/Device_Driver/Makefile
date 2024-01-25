obj-m += CENG322_devdriver.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	sudo dmesg -C
	sudo insmod CENG322_devdriver.ko
	sudo rmmod CENG322_devdriver.ko
	dmesg
