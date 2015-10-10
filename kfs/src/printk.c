/*
** printk.c for printk in /home/champi_f/Kernel/ProjectOne/fromScratch/src
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Sat Oct 10 14:33:51 2015 Florian Champin
** Last update Sat Oct 10 22:56:50 2015 Florian Champin
*/

#include "system.h"

/* You will need to code these up yourself!  */
unsigned char *memcpy(void *dest, const void *src, size_t count)
{
  size_t i;
  unsigned char *tmp = (unsigned char *)dest;
  for (i = 0; i < count; i++)
    tmp[i] = ((unsigned char *)src)[i];
  return tmp;
}

unsigned char *memset(void *dest, unsigned char val, size_t count)
{
  size_t i;
  unsigned char *tmp = (unsigned char *)dest;
  for (i = 0; i < count; i++)
    tmp[i] = val;
  return tmp;
}

unsigned short *memsetw(void *dest, unsigned short val, size_t count)
{
  size_t i;
  unsigned short *tmp = (unsigned short *)dest;
  for (i = 0; i < count; i++)
    tmp[i] = val;
  return tmp;
}

size_t strlen(const char *str)
{
  /* This loops through character array 'str', returning how
   *  many characters it needs to check before it finds a 0.
   *  In simple words, it returns the length in bytes of a string */
  size_t retval;
  for(retval = 0; str[retval] != '\0'; retval++)
    {}
  return retval;
}

/* We will use this later on for reading from the I/O ports to get data*  from devices such as the keyboard. We are using what is called
 *  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
  unsigned char rv;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. this*  will be used in the next tutorial for changing the textmode cursor
 *  position. Again, we use some inline assembly for the stuff that simply
 *  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/* This is a very simple main() function. All it does is sit in any*  infinite loop. This will be like our 'idle' loop */
void main()
{
  init_video();
  cls();
  puts("TEST\n");
  for (;;);
}
