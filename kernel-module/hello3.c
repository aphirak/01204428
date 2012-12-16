#include <linux/module.h>       
#include <linux/kernel.h>  
#include <linux/init.h> 

static int hello_init(void)
{
  printk(KERN_INFO "Hello world!2\n");
  return 0;   
}
module_init(hello_init);


static void hello_cleanup(void)
{
  printk(KERN_INFO "Cleaning up module.2\n");
}
module_exit(hello_cleanup);

