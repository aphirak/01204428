#include <linux/module.h>       
#include <linux/kernel.h>  
#include <linux/init.h>

#define DRIVER_AUTHOR "Aphirak Jansang <aphirak.j@ku.ac.th>"
#define DRIVER_DESC   "A sample driver"

static char *mystring = "my foo name";
module_param(mystring, charp, 000); 
MODULE_PARM_DESC(mystring, "A character string");

static int __init hello5_init(void)
{
  printk(KERN_INFO "Hello world!\n");
  printk(KERN_INFO "Your name is %s\n", mystring);
  return 0;   
}
module_init(hello5_init);

static void __exit hello5_cleanup(void)
{
  printk(KERN_INFO "Cleaning up module.5\n");
}
module_exit(hello5_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);	
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");

