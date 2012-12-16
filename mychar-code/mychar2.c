#include <linux/module.h>       
#include <linux/kernel.h>  
#include <linux/init.h> 


#include <linux/fs.h>
static dev_t first;

#include <linux/cdev.h>
#include <linux/device.h>
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

static int __init mychar_init(void)
{
   int ret;

   /*initialization content placed here*/   
   printk( KERN_INFO "install module\n");

   first = MKDEV(0, 15);
   ret = alloc_chrdev_region(&first, 0, 3, "myc");

   if (ret < 0) {
     printk(KERN_INFO "Major number allocation is failed\n");
     return -1;
   }

   if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
   {
      unregister_chrdev_region(first, 1);
      return -1;
   }

   if (device_create(cl, NULL, first, NULL, "mychar") == NULL)
   {
     class_destroy(cl);
     unregister_chrdev_region(first, 1);
     return -1;
   }

   return 0;
}

static void __exit mychar_cleanup(void)
{
   /*cleanup module placed here*/
   device_destroy(cl, first);
   class_destroy(cl);
   unregister_chrdev_region(first, 1);

   printk( KERN_INFO "remove module\n");
}

module_init(mychar_init);
module_exit(mychar_cleanup);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Char Device Driver");
MODULE_AUTHOR("Aphirak Jansang");
