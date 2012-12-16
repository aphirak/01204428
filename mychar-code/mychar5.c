#include <linux/module.h>       
#include <linux/kernel.h>  
#include <linux/init.h> 


#include <linux/fs.h>
static dev_t first;

#include <linux/cdev.h>
#include <linux/device.h>
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

#include <linux/uaccess.h>

static int my_open(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: open()\n");
  return 0;
}

static int my_close(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: close()\n");
  return 0;
}

static char c;

static ssize_t my_read(struct file *f, char __user *buf, size_t
  len, loff_t *off)
{
  printk(KERN_INFO "Driver: read()\n");
  if (copy_to_user(buf, &c, 1) != 0) 
      return -EFAULT;
  else
      return 1;
}

static ssize_t my_write(struct file *f, const char __user *buf,
  size_t len, loff_t *off)
{
  printk(KERN_INFO "Driver: write()\n");
  if (copy_from_user(&c, buf + len - 1, 1) != 0)
      return -EFAULT;
  else
      return len;
}

static struct file_operations pugs_fops =
{
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_close,
  .read = my_read,
  .write = my_write
};

static int __init mychar_init(void)
{
   int ret;

   /*initialization content placed here*/   
   printk( KERN_INFO "install module\n");

   //first = MKDEV(0, 15);
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

   cdev_init(&c_dev, &pugs_fops);
   if (cdev_add(&c_dev, first, 1) == -1)
   {
     device_destroy(cl, first);
     class_destroy(cl);
     unregister_chrdev_region(first, 1);
    return -1;
   }

   return 0;
}

static void __exit mychar_cleanup(void)
{
   /*cleanup module placed here*/
   cdev_del(&c_dev);
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
