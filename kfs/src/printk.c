/*
** printk.c for printk in /home/champi_f/Kernel/ProjectOne/fromScratch/src
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Sat Oct 10 14:33:51 2015 Florian Champin
** Last update Mon Oct 12 19:40:47 2015 Florian Champin
*/

#include "vfb.h"

unsigned char inportb (unsigned short _port)
{
  unsigned char rv;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

#define PORT 0x3f8 /* COM1 */

void init_serial()
{
  outportb(PORT + 0, 0x03);
  outportb(PORT + 3, 0x03);
}

void main()
{
  vfb_clear();
  int i = 0;
  char l = 48;
  for (i = 0; i < 20000; ++i) {
    vfb_putstr(&l, 1);
    ++l;
    if (l > 90)
      l = 48;
    unsigned int j;
    for (j = 0; j <  1083647; ++j){
    }
  }
  for (;;);
}
