/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include "efm32gg.h"


#define DEVICE_NAME "GPIO_GAMEPAD"

irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs);

static ssize_t gpio_read(struct file* filp, char __user* buff, size_t count, loff_t* offp);
static ssize_t gpio_write(struct file* filp, const char __user* buff, size_t count,  loff_t* offp);
static int gpio_open(struct inode∗ inode, struct file* filp);
static int gpio_release(struct inode∗ inode, struct file* filp);
static int gpio_fasync(int fd, struct file* filp, int mode);




static dev_t dev_num;
struct cdev gpio_cdev;
struct fasync_struct* async_queue;

static struct file_operations gpio_fops = {
  .owner = THIS_MODULE,
  .read = gpio_read,
  .write = gpio_write,
  .open = gpio_open,
  .release = gpio_release,
  .fasync = gpio_fasync
};




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
    return -1;
  }

  // setup I/O ports:
  if (!request_mem_region(GPIO_PC_MODEL, 4, DRIVER_NAME)) {
    printk("FAILURE TO ALLOCATE: GPIO_PC_MODEL");
    return -1;
  }
  if (!request_mem_region(GPIO_PC_DOUT, 4, DRIVER_NAME)) {
    printk("FAILURE TO ALLOCATE: GPIO_PC_DOUT");
    return -1;
  }

  if (!request_mem_region(GPIO_EXTIPSELL, 4, DRIVER_NAME)) {
    printk("FAILURE TO ALLOCATE: GPIO_EXTIPSELL");
    return -1;
  }

  if (!request_mem_region(GPIO_EXTIFALL, 4, DRIVER_NAME)) {
    printk("FAILURE TO ALLOCATE: GPIO_EXTIFALL");
    return -1;
  }

  if (!request_mem_region(GPIO_IEN, 4, DRIVER_NAME)) {
    printk("FAILURE TO ALLOCATE: GPIO_IEN");
    return -1;
  }
  if (!request_mem_region(GPIO_IFC, 4, DRIVER_NAME)) {
    printk("FAILURE TO ALLOCATE: GPIO_IFC");
    return -1;
  }

  // set up GPIO registers!
  iowrite32(0x33333333, GPIO_PC_MODEL); /* set pins 0-7 to input */
  iowrite32(0xff,       GPIO_PC_DOUT); /* internal pullup ... */
  iowrite32(0x22222222, GPIO_EXTIPSELL);

  // set up GPIO interrupts!
  if (request_irq(17, interrupt_handler, 0, DEVICE_NAME, &gpio_cdev) || // EVEN
      request_irq(18, interrupt_handler, 0, DEVICE_NAME, &gpio_cdev)) { // ODD
    printk("FAILURE request_irq!");
    return -1;
  }

  iowrite32(0xff,       GPIO_EXTIFALL);
  iowrite32(0xff,       GPIO_IEN);
  iowrite32(0xff,       GPIO_IFC);


  // initialize cdev, see pg. 56&57 cp 3 ldd
  cdev_init(&gpio_cdev, &gpio_fops);
  cdev.owner = THIS_MODULE;
  cdev.ops = &gpio_fops;

  if (cdev_add(&gpio_cdev, dev_num,1)) {
    printk("FAILURE cdev_add");
    return -1;
  }
  struct class* cl;
  cl = class_create(THIS_MODULE, DRIVER_NAME);
  device_create(cl, NULL, dev_num, NULL, DRIVER_NAME);z3


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
    return;
  }
  printk("Short life for a small module...\n");
}

irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs) {
  // mark interrupt as handled
  iowrite32(0xff, GPIO_IFC);
  if (async_queue)
    kill_fasync(&async_queue, SIGIO, POLL_IN);

  printk("Interrupt successfully handled.");
  return IRQ_HANDLED;
}


static ssize_t gpio_read(struct file* filp, char __user* buff, size_t count, loff_t* offp) {
  //http://www.gnugeneration.com/mirrors/kernel-api/r4299.html
  uint8_t gpio_button_state = ioread8(GPIO_PC_DIN);
  if (copy_to_user(buff, &gpio_button_state, 1)) {
    printk("READ FAILURE Could not copy all data!");
    return 0;
  }
  return 1; // byte length, not error code
}

static ssize_t gpio_write(struct file* filp, const char __user* buff, size_t count,  loff_t* offp) {
  printk("GPIO WRITTEN?!");
  return 0;
}

static int gpio_open(struct inode∗ inode, struct file* filp) {
  printk("GPIO OPENED?!");
  return 0;
}

static int gpio_release(struct inode∗ inode, struct file* filp) {
  printk("GPIO RELEASED?!");
  return 0;
}

static int gpio_fasync(int fd, struct file* filp, int mode) {
  // pg 171 cp 09 in ldd
  return fasync_helper(fd, filp, mode, async_queue);
}

module_init(gpio_init);
module_exit(gpio_cleanup);

MODULE_DESCRIPTION("HUGE module, demo only, not very useful.");
MODULE_LICENSE("MIT");
