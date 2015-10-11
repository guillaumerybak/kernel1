/*
** system.h for system in /home/champi_f/Kernel/ProjectOne/fromScratch
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Sat Oct 10 14:58:18 2015 Florian Champin
** Last update Sat Oct 10 22:53:18 2015 Florian Champin
*/

#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef int size_t;

/* MAIN.C */
extern unsigned char *memcpy(void *dest, const void *src, size_t count);
extern unsigned char *memset(void *dest, unsigned char val, size_t count);
extern unsigned short *memsetw(void *dest, unsigned short val, size_t count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

//scrn.c
extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

#endif
