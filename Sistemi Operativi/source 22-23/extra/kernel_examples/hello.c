#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int init_hello(void) {
  printk(KERN_INFO "hello world\n");
  return 0;
};

static void cleanup_hello(void) {
  printk(KERN_INFO "goodbye world\n");
};

module_init(init_hello);
module_exit(cleanup_hello);
