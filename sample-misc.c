#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

static int sample_misc_open(struct inode *inode, struct file *file) {
    printk(KERN_DEBUG "sample misc open\n");
    return 0;
}

static int sample_misc_release(struct inode *inode, struct file *file) {
    printk(KERN_DEBUG "sample misc release\n");
    return 0;
}

static ssize_t sample_misc_read(struct file *file, char __user *data, size_t size, loff_t *offset) {
    return size;
}

static ssize_t sample_misc_write(struct file *file, const char __user *data, size_t size, loff_t *offset) {
    return size;
}

static struct file_operations sample_misc_fops = {
    .owner = THIS_MODULE,
    .open = sample_misc_open,
    .release = sample_misc_release,
    .read = sample_misc_read,
    .write = sample_misc_write,
};

static struct miscdevice sample_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "sample-misc",
    .fops = &sample_misc_fops,
};

static int __init sample_misc_init(void) {
    int result;
    printk(KERN_INFO "sample misc init\n");
    result = misc_register(&sample_misc_device);
    return result;
}

static void __exit sample_misc_exit(void) {
    printk(KERN_INFO "sample misc exit\n");
    misc_deregister(&sample_misc_device);
}

module_init(sample_misc_init);
module_exit(sample_misc_exit);

