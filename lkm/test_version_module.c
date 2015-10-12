#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "version.h"

int main() {
  int fd = open("/dev/version", O_RDWR);

  int id = ioctl(fd, VERSION_RESET);
  printf("%d\n", id);
  close(fd);
  return id;
}
