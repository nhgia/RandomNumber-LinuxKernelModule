# Random Number Generator - Linux Kernel Module
> CS333 - Introduction to Operating Systems | Ho Chi Minh University of Science - VNU.

*Spring 2020 Course*

**PROJECT #1**: Build a Linux kernel module to generate random integer number, allow User Space can open and read. 

#### Author:
- 1751064 - Nguyen Hoang Gia 
- 1751063 - Pham Bao Duy


### Prerequisite
- Ubuntu / Linux
- Download or clone the project.
- Install essential components by running:
```shell
sudo apt-get install build-essential
```
- Change directory to the project folder.

### Step 1: Compile module in Kernel Space and User Space
- Simply by running
```shell
make
```

### Step 2: Insert module into the kernel & grant permission
- Run 
```shell
sudo insmod random_module.ko
```
- Next, run 
```shell
sudo chmod 777 /dev/RndNum
```

### Step 3: Get random number from user space
- Run this command
```shell
./random_module_userspace
```
- Check the output, it will be some random number.

### Step 4: Remove module from the kernel and clean up
- First, run
```shell
sudo rmmod random_module.ko
```
- Then
```shell
make clean
```
