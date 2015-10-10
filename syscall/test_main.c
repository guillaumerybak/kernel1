#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  long int b;
  
  long int a = syscall(325, &b);
  printf("System call returned %ld %ld\n", a, b);
  return 0;
}

