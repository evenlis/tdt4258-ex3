/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include "efm32gg.h"


#define DEVICE_NAME "8 BUTTON GAMEPAD"

irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs);

static dev_t dev_num;
struct cdev gpio_cdev;

static struct file_operations gpio_fops = {
  owner = THIS_MODULE,
  read = gpio_read,
  write = gpio_write ,
  open = gpio_open,
  release = gpio_release
};
static int gpio_open(struct inode∗ inode, struct file* filp);
static int gpio_release(struct inode∗ inode, struct file* filp);
static ssize_t gpio_read(struct file* filp, char __user* buff, size_t count, loff_t* offp);
static ssize_t gpio_write(struct file* filp, const char __user* buff, size_t count,  loff_t* offp);



/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */


static int __init gpio_init(void) {
  printk("Initializing %s driver...", DEVICE_NAME);

  // fetch device num, see pg. 45 in ldd (cp. 3)
  if (alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME)) {
    printk("FAILURE alloc_chrdev_regeion!");
    return 1;
  }
  // 0. cdev shit --??
  cdev_init(&gpio_cdev, &gpio_fops);


  // 1. set up GPIO registers!
  iowrite32(0x33333333, GPIO_PC_MODEL); /* set pins 0-7 to input */
  iowrite32(0xff,       GPIO_PC_DOUT); /* internal pullup ... */
  iowrite32(0x22222222, GPIO_EXTIPSELL);

  // 2. set up GPIO interrupts!
  if (request_irq(17, interrupt_handler, 0, DEVICE_NAME, &gpio_cdev) || // EVEN
      request_irq(18, interrupt_handler, 0, DEVICE_NAME, &gpio_cdev)) { // ODD
    printk("FAILURE request_irq!");
    return 1;
  }



  iowrite32(0xff,       GPIO_EXTIFALL);
  iowrite32(0xff,       GPIO_IEN);
  iowrite32(0xff,       GPIO_IFC);

  // 3. more shit
  printk("Hello World, here is your GPIO-module speaking\n");
  return 0;
}

/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit gpio_cleanup(void) {

  // see pg. 45 cp 3 ldd
  if (unregister_chrdev_region(&dev_num, 1)) {
    printk("FAILURE unregister");
    exit 1;
  }
  printk("Short life for a small module...\n");
}

irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs) {


}



module_init(gpio_init);
module_exit(gpio_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");
