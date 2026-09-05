#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
/* This function is called when the module is loaded. */
int simple_init(void)
{
   printk(KERN_INFO "Loading Kernel Module\n");
   printk(KERN_INFO "%1u\n", GOLDEN_RATIO_PRIME);
   printk(KERN_INFO "jiffies = %1u\n", jiffies);
   printk(KERN_INFO "HZ = %u\n", HZ);
   return 0;
}
 
/* This function is called when the module is removed. */
void simple_exit(void)
{
   printk(KERN_INFO "Removing Kernel Module\n");
   printk(KERN_INFO "GCD of 3300 and 24 is %1u\n", gcd(3300, 24));
   printk(KERN_INFO "jiffies = %1u\n", jiffies);
}
 
/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");