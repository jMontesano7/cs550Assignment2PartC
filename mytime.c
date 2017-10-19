#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("DUAL BSD/GPL");


int __init init_module(void);
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

int __init init_module()
{
	//return -1;  TEST
	if(misc_register(&my_time) != 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void __exit my_exit(void)
{
	misc_deregister(&my_time);
}
static ssize_t my_read(struct file *file, char __user *out, size_t size, loff_t *off)
{
	int size1 = 1000;
	char buff[size1];
	struct timespec kernTime = current_kernel_time();
	struct timespec timeDay;
	getnstimeofday(&timeDay);
	
	sprintf(buff, "Current_Kernel_Time(): %lu %lu \n GetNsTimeOfDay(): %lu %lu", kernTime.tv_sec, kernTime.tv_nsec,timeDay.tv_sec,timeDay.tv_nsec);
	
	if(copy_to_user(out, buff, size1+1) != 0)
	{
		printk(KERN_ALERT "ERROR IN COPY_TO_USER");
		return -1;
	}
	return size1;
}
static int my_open(struct inode *inode, struct file *file)
{
	return 0;
}
static int my_close(struct inode *inodep, struct file *filp)
{
	return 0;
}
