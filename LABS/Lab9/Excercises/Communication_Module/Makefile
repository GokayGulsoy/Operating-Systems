obj-m += CENG322_comuserapp.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	sudo dmesg -C
	sudo insmod CENG322_comuserapp.ko
	sudo rmmod CENG322_comuserapp.ko
	dmesg
