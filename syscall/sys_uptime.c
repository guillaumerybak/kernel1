#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE1(uptime, time_t __user *, in)
{
	static struct timespec uptime;

	get_monotonic_boottime(&uptime);
	if (in)
		*in = (time_t)uptime.tv_sec;
	return (*in);
}
