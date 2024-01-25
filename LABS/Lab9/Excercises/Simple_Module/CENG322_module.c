#include <linux/init.h> // for the macros
#include <linux/module.h> // used by all modules
#include <linux/kernel.h> // for KERN_INFO

MODULE_LICENSE("GPL");
MODULE_AUTHOR("A. Yigit");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

static int __init my_init(void) {
 printk(KERN_INFO "Hello, World!\n");
 return 0;
}
static void __exit my_exit(void) {
 printk(KERN_INFO "Goodbye, World!\n");
}
module_init(my_init);
module_exit(my_exit);
