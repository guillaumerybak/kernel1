#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/printk.h>

#include "version.h"

#define MAX_VERSION_STRING_LENGTH 128

static char m_current_version[MAX_VERSION_STRING_LENGTH];
static size_t m_len = 0;
static int m_version_modified = 0;
static int m_version_device_in_use = 0;

static void version_set_default(void)
{
	/* m_len = snprintf(m_current_version, */
	/* 		 MAX_VERSION_STRING_LENGTH, */
	/* 		 linux_proc_banner, */
	/* 		 utsname()->sysname, */
	/* 		 utsname()->release, */
	/* 		 utsname()->version); */
	m_len = snprintf(m_current_version,
			 MAX_VERSION_STRING_LENGTH,
			 "%s version %s %s\n",
			 utsname()->sysname,
			 utsname()->release,
			 utsname()->version);
}

static void version_update_current(const char *version, const int length)
{
	strncpy(m_current_version, version, (length > MAX_VERSION_STRING_LENGTH
					     ? MAX_VERSION_STRING_LENGTH
					     : length));
	m_len = length;
	m_version_modified = 1;
}

static ssize_t version_read(struct file *file, char __user *buffer, size_t count, loff_t *off)
{
	static size_t m_current = 0;
	if (*off != 0) {
		return 0;
	}
	if (m_current >= m_len) {
		m_current = 0;
		return 0;
	}
	m_current += count;
	strncpy(buffer, m_current_version, (count > m_len ? m_len : count));
	return (count > m_len ? m_len : count);
}

static ssize_t version_write(struct file *file, const char __user *buffer, size_t count, loff_t *off)
{
	printk("VERSION WRITE CALLED %lu", count);
	version_update_current(buffer, count);
	return count;
}

static long version_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
	case VERSION_MODIFIED: return m_version_modified; break;
	case VERSION_RESET: version_set_default(); break;
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

static struct file_operations file_ops = {
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
	if ((ret = misc_register(&misc_device)) < 0) {
		pr_warn("misc_register() failed: %d\n", ret);
		return -ENOMEM;
	}
	version_set_default();
	return ret;
}

static void __exit version_exit(void)
{
	misc_deregister(&misc_device);
}

module_init(version_init);
module_exit(version_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Guillaume Rybak");
MODULE_DESCRIPTION("EPITECH --- Kernel Version Misc Device");
