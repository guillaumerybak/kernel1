#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#include "version.h"

#define MAX_VERSION_STRING_LENGTH 128

static char *m_current_version;
static size_t m_len;
static char m_version_modified;
static char m_version_device_in_use;

static void version_set_default(void)
{
	m_len = snprintf(m_current_version,
			 MAX_VERSION_STRING_LENGTH,
			 "%s version %s %s\n",
			 utsname()->sysname,
			 utsname()->release,
			 utsname()->version);
}

static ssize_t version_read(struct file *file, char __user *buffer,
			    size_t count, loff_t *off)
{
	unsigned long len = (count > (m_len - *off)
			     ? (m_len - *off)
			     : count);

	if (*off >= m_len)
		return 0;
	if (copy_to_user(buffer, m_current_version + *off, len))
		return -EFAULT;
	*off += len;
	return (count > m_len ? m_len : count);
}

static ssize_t version_write(struct file *file, const char __user *buffer,
			     size_t count, loff_t *off)
{
	unsigned long n = 0;

	n = copy_from_user(m_current_version, buffer,
			   (count > MAX_VERSION_STRING_LENGTH
			    ? MAX_VERSION_STRING_LENGTH
			    : count));
	m_len = count - n;
	m_version_modified = 1;
	return count;
}

static long version_ioctl(struct file *file, unsigned int cmd,
			  unsigned long arg)
{
	switch (cmd) {
	case VERSION_MODIFIED:
		return m_version_modified;
	case VERSION_RESET:
		version_set_default();
		break;
	default: return -ENOTTY;
	}
	return 0;
}

static int version_open(struct inode *inode, struct file *file)
{
	return (m_version_device_in_use++ ? -EBUSY : 0);
}

static int version_release(struct inode *inode, struct file *file)
{
	--m_version_device_in_use;
	return 0;
}

static const struct file_operations file_ops = {
	.owner		= THIS_MODULE,
	.open		= version_open,
	.read		= version_read,
	.write		= version_write,
	.unlocked_ioctl	= version_ioctl,
	.release	= version_release,
};

static struct miscdevice misc_device = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "version",
	.fops		= &file_ops,
};

static int __init version_init(void)
{
	int ret;

	ret = misc_register(&misc_device);
	if (ret < 0) {
		pr_warn("misc_register() failed: %d\n", ret);
		return -ENOMEM;
	}
	m_current_version = kmalloc(MAX_VERSION_STRING_LENGTH, GFP_KERNEL);
	if (m_current_version == NULL)
		return -ENOMEM;
	version_set_default();
	return ret;
}

static void __exit version_exit(void)
{
	misc_deregister(&misc_device);
	kfree(m_current_version);
}

module_init(version_init);
module_exit(version_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Guillaume Rybak");
MODULE_DESCRIPTION("EPITECH --- Kernel Version Misc Device");
