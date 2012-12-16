#include <linux/module.h>       
#include <linux/kernel.h>  
#include <linux/init.h>

static int hello3_data __initdata = 3; 


static int __init  hello3_init(void)
{
    printk(KERN_INFO "Hello world!\n");
    return 0;   
}

static void __exit hello3_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello3_init);
module_exit(hello3_cleanup);
