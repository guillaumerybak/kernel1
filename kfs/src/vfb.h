/*
** vfb.h for vfb in /home/champi_f/Kernel/ProjectOne/fromScratch/src
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Mon Oct 12 13:17:38 2015 Florian Champin
** Last update Mon Oct 12 14:58:13 2015 Florian Champin
*/

#ifndef VFB_H_
# define VFB_H_

#define NB_LINE 25
#define NB_COL	80
#define VBF_ADD	(void *)0xB8000

typedef struct		s_vfb {
  struct
  {
    int			x;
    int			y;
  }			pos;
  unsigned short	*buffer;
  unsigned char		color;
}			t_vfb;

void vfb_clear();

#endif /* !VFB_H_ */
