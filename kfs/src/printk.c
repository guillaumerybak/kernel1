/*
** printk.c for printk in /home/champi_f/Kernel/ProjectOne/fromScratch/src
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Sat Oct 10 14:33:51 2015 Florian Champin
** Last update Sat Oct 10 16:28:41 2015 Florian Champin
*/

#include "system.h"

/* You will need to code these up yourself!  */
void *memcpy(void *dest, const void *src, size_t count)
{
  /* Add code here to copy 'count' bytes of data from 'src' to    *  'dest', finally return 'dest' */
  const char *sp = (const char *)src;
  char *dp = (char *)dest;
  for(; count != 0; count--) *dp++ = *sp++;
  return dest;
}

void *memset(void *dest, unsigned char val, size_t count)
{
  /* Add code here to set 'count' bytes in 'dest' to 'val'.
   *  Again, return 'dest' */
  char *temp = (char *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
  /* Same as above, but this time, we're working with a 16-bit
   *  'val' and dest pointer. Your code can be an exact copy of    *  the above, provided that your local variables if any, are
   *  unsigned short */
  unsigned short *temp = (unsigned short *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

size_t strlen(const char *str)
{
  /* This loops through character array 'str', returning how
   *  many characters it needs to check before it finds a 0.
   *  In simple words, it returns the length in bytes of a string */
  size_t retval;
  for(retval = 0; *str != '\0'; str++) retval++;
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