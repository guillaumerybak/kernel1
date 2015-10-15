/*
** printk.c for printk in /home/champi_f/Kernel/ProjectOne/fromScratch/src
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Sat Oct 10 14:33:51 2015 Florian Champin
** Last update Thu Oct 15 13:58:01 2015 Florian Champin
*/

#include "vfb.h"

/* Defines Serial Ports Base Address */
/* COM1 0x3F8                        */
/* COM2 0x2F8                */
/* COM3 0x3E8                */
/* COM4 0x2E8                */

#define BASE 0x3f8
#define DLL (base + 0)
#define DLH (base + 1)

#define TXD (base + 0)
#define RXD (base + 0)
#define IER (base + 1)
#define IIR (base + 2)
#define LCR (base + 3)
#define LSR (base + 4)
#define MCR (base + 5)
#define MSR (base + 6)


#define PORT 0x3F8 /* COM1 */

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

void init_serial()
{
  outportb(PORT + 1, 0x00);    // Disable all interrupts
  /* PORT Communication Settings */
  outportb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
  outportb(PORT + 0, 0x03);    // Set baud rate divisor to 3 (low byte) 38400 baud
  outportb(PORT + 1, 0x00);    // Set baud rate divisor  Latch High Bite (hi byte)
  outportb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bits
  outportb(PORT + 2 , 0xC7);  /* FIFO Control Register */
  outportb(PORT + 4 , 0x0B);  /* Turn on DTR, RTS, and OUT2 */
}

void	printk(const char *msg) {
  int	i;
  init_serial();
  vfb_clear();

  for (i = 0; msg[i] != '\0'; ++i)
    outportb(PORT, msg[i]);
  vfb_putstr(msg, i);
}

/*
int serial_received() {
  return inportb(PORT + 5) & 1;
}

char read_serial() {
  while (serial_received() == 0);

  return inportb(PORT);
}

int is_transmit_empty() {
  return inportb(PORT + 5) & 0x20;
}

void write_serial(char a) {
  while (is_transmit_empty() == 0);

  outportb(PORT,a);
}
*/
