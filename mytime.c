#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("DUAL BSD/GPL");


static ssize_t my_read(struct file *file, char __user *out, size_t size, loff_t *off);
static int my_open(struct inode *inode, struct file *file);
static int my_close(struct inode *inodep, struct file *filp);


static struct file_operations my_fops = {
.owner = THIS_MODULE,
.open = my_open,
.release = my_close,
.read = my_read,
};

static struct miscdevice my_time = {
.minor = MISC_DYNAMIC_MINOR,
.name = "mytime",
.fops = &my_fops
};

static int __init my_module_init(void)
{
	if(misc_register(&my_time) != 0)
	{
		printk(KERN_ALERT "mytime: Issue with registering device\n");
		return -1;
	}
	else
	{
		printk(KERN_ALERT "Mytime module registered corectly! \n");
		return 0;
	}
}

static void __exit my_exit(void)
{
	misc_deregister(&my_time);
}
static ssize_t my_read(struct file *file, char __user *out, size_t size, loff_t *off)
{

}
static int my_open(struct inode *inode, struct file *file)
{
	if(my_module_init() != 0){
	
		printk(KERN_ALERT "ISSUE WITH OPEN");
		return -1;
	}
	else{
		printk(KERN_ALERT "OPEN SUCCESSFUL");
		return 0;
	}
}
static int my_close(struct inode *inodep, struct file *filp)
{

}
