#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/seq_file.h>

static int version_proc_read()
{
}

static int version_proc_open(struct inode *inode, struct file * file)
{
  printk("VERSION OPEN CALLED");
}

static const struct file_operations version_proc_fops = {
  .open		= version_proc_open,
  .read		= seq_read,
  .llseek	= seq_lseek,
  .release	= single_release,
};

static int __init proc_version_init(void)
{
  proc_create("sys/kernel/version", 0, NULL, &version_proc_fops);
  return 0;
}

fs_initcall(proc_version_init);
