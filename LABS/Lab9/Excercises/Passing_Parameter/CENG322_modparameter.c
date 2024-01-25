#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("A. Yigit");
MODULE_DESCRIPTION("Parameter passing for screen module.");
MODULE_VERSION("0.01");

static int curr_brightness = 1;
static char *auto_adjust = "yes";
static int aspect_ratio[2] = { 16, 9 }; // wide screen
static int arg_size = 0;

/* module_param(foo, int, 0000)
 * The first param is the parameters name.
 * The second param is its data type.
 * The final argument is the permissions bits,
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 */

 module_param(curr_brightness, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
 MODULE_PARM_DESC(curr_brightness, "Brightness value(0-100)");
 module_param(auto_adjust, charp, S_IRUSR | S_IWUSR);
 MODULE_PARM_DESC(auto_adjust, "Auto adjustment value for brightness (yes/no)");

 /* module_param_array(name, type, num, perm);
  * The first param is the parameter's (in this case the array's) name.
  * The second param is the data type of the elements of the array.
  * The third argument is a pointer to the variable that will store the number
  * of elements of the array initialized by the user at module loading time.
  * The fourth argument is the permission bits.
  */

 module_param_array(aspect_ratio, int, &arg_size, 0000);
 MODULE_PARM_DESC(aspect_ratio, "An array of integers");

static int __init my_init(void) {

  int i;

  printk(KERN_INFO "Module is initializing ...\n");
  printk(KERN_INFO "Brightness: %d\n", curr_brightness);

  printk(KERN_INFO "Can the module adjust brightness auto? %s\n", auto_adjust);

  for (i = 0; i < ARRAY_SIZE(aspect_ratio); i++)
      printk(KERN_INFO "aspect_ratio[%d] = %d\n", i, aspect_ratio[i]);

  printk(KERN_INFO "got %d arguments for myintarray.\n", arg_size);
  return 0;
}

static void __exit my_exit(void) {
 printk(KERN_INFO "Goodbye, World!\n");
}

module_init(my_init);
module_exit(my_exit);
