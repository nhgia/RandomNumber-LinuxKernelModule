#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/device.h>

#define DRIVER_AUTHOR		"Nguyen Hoang Gia <1751064> Pham Bao Duy <1751063>"
#define DRIVER_DESC 		"Project 1 Random Number Generator"
#define DRIVER_VERSION 		"0.1"
#define DEVICE_NAME		"RndNum"
#define DEVICE_CLASS_NAME	"class_RndNum"
struct _rndnum_drv {
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev;
}_rndnum_drv;

// ------------ Function declaration, header file ------------
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);

// ------------ File structure ------------ 
static struct file_operations fops = {
  .read = device_read,
  .open = device_open,
  .release = device_release
};

// ------------ Global variables ------------ 
static bool isDeviceOpen = false;

// ------------ Driver initialize ------------ 
static int __init init_project(void)
{
	int devNum = 0;
	//Dynamic device number assigning
	_rndnum_drv.dev_num = 0;
	devNum = alloc_chrdev_region(&_rndnum_drv.dev_num, 0, 1, DEVICE_NAME);
	if (devNum < 0) {
     		printk("Assigning major number %d failed \n", devNum);
		return devNum;
   	}

	// Create device class
	_rndnum_drv.dev_class = class_create(THIS_MODULE, DEVICE_CLASS_NAME);
	if (_rndnum_drv.dev_class == NULL) {
		printk("Create device class failed.\n");
		unregister_chrdev_region(_rndnum_drv.dev_num, 1);
		return 0;
	};

	// Create device
	_rndnum_drv.dev = device_create(_rndnum_drv.dev_class, NULL, _rndnum_drv.dev_num, NULL, DEVICE_NAME);
	if (IS_ERR(_rndnum_drv.dev)) {
		printk("Create device failed.\n");
		class_destroy(_rndnum_drv.dev_class);
		unregister_chrdev_region(_rndnum_drv.dev_num, 1);
		return 0;
	};

	printk("RndNum initialized successfully.\n");
	return 0;
};


// ------------ Driver exit ------------ 
static void __exit exit_project(void)
{

	// Relase device class and device file
	device_destroy(_rndnum_drv.dev_class, _rndnum_drv.dev_num);
	class_destroy(_rndnum_drv.dev_class);
	
	// Release device number
	unregister_chrdev_region(_rndnum_drv.dev_num, 1);
	printk("RndNum removed and un-plugged successfully.\n");
};

// ------------ Device specific ------------ 
// Open device file
static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	if (isDeviceOpen == true) return -EBUSY;
	isDeviceOpen = true;
	printk("Total time that open device: %d \n", ++counter);
	return 0;
}

// Close device file
static int device_release(struct inode *inode, struct file *file)
{
	isDeviceOpen = false;
	printk("Device released.\n");
	return 0;
}

// Read device
static ssize_t 	device_read(struct file *fileProcess,
		char *buffer,    // Character buffer
		size_t length,   // Buffer length
		loff_t *offset)  // Offset
{
   /* Number of bytes actually written to the buffer */
   int bytes_read = 0;

   /* If we're at the end of the message, return 0 signifying end of file */
   if (*msg_Ptr == 0) return 0;

   /* Actually put the data into the buffer */
   while (length && *msg_Ptr)  {

        /* The buffer is in the user data segment, not the kernel segment;
         * assignment won't work.  We have to use put_user which copies data from
         * the kernel data segment to the user data segment. */
         put_user(*(msg_Ptr++), buffer++);

         length--;
         bytes_read++;
   }

   /* Most read functions return the number of bytes put into the buffer */
   return bytes_read;
}



module_init(init_project);
module_exit(exit_project);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
