#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("A. Yigit");
MODULE_DESCRIPTION("Communication  module.");
MODULE_VERSION("0.01");

static struct proc_dir_entry* proc_entry;
static ssize_t custom_read(struct file* file, char __user* user_buffer, size_t count, loff_t* offset)
{
   printk(KERN_INFO "Calling our very own custom read method.");
   char message[] = "You read data!\n";
   int message_length = strlen(message);
   if (*offset > 0)
    return 0;
   copy_to_user(user_buffer, message, message_length);
   *offset = message_length;
   return message_length;
}

static struct file_operations fops =
{
 .owner = THIS_MODULE,
 .read = custom_read
};

// Custom init and exit methods
static int __init custom_init(void) {
 proc_entry = proc_create("iytecommodule", 0666, NULL, &fops);
 printk(KERN_INFO "Communication driver loaded.");
 return 0;
}

static void __exit custom_exit(void) {
 proc_remove(proc_entry);
 printk(KERN_INFO "Goodbye ...");
}

module_init(custom_init);
module_exit(custom_exit);
