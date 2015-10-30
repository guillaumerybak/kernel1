#include <linux/kernel.h>
#include <linux/syscalls.h>

static time_t do_uptime(time_t __user *in)
{
	static struct timespec uptime;

	get_monotonic_boottime(&uptime);
	if (in) {
		if (copy_to_user(in, &uptime.tv_sec, sizeof(*in)))
			return ((time_t) -1);
	}
	return uptime.tv_sec;
}

SYSCALL_DEFINE1(uptime, time_t __user *, in)
{
	return do_uptime(in);
}
