KDIR = /lib/modules/`uname -r`/build
all :
	make -C $(KDIR) M=`pwd`
	$(CC) random_module_userspace.c -o random_module_userspace
clean :
	make -C $(KDIR) M=`pwd` clean
	rm random_module_userspace
