# RandomNumber-LinuxKernelModule
A Linux Kernel Module to generate random integer number.

--
make
sudo insmod random_module.ko
sudo chmod 777 /dev/RndNum
gcc -c random_module_userspace.c 
gcc -o random_module_userspace random_module_userspace.o
./random_module_userspace
sudo rmmod random_module.ko
