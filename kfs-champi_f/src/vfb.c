/*
** vfb.c for vfb in /home/champi_f/Kernel/ProjectOne/fromScratch/src
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Mon Oct 12 13:17:38 2015 Florian Champin
** Last update Mon Oct 12 19:39:42 2015 Florian Champin
*/

#include "string.h"
#include "vfb.h"

static struct s_vfb vfb = {
  .pos = { .x = 0, .y = 0},
  .color = 0x07,
  .buffer = VBF_ADD,
};

static inline void	scroll_up() {
  int	i;
  for (i = 0; i < (NB_LINE - 1) * NB_COL; ++i) {
    vfb.buffer[i] = vfb.buffer[i + NB_COL];
  }

  for (; i < NB_LINE * NB_COL; ++i)
    vfb.buffer[i] = (vfb.color << 8) | ' ';

  vfb.pos.y--;
}

static inline void	new_line() {
  vfb.pos.x = 0;
  vfb.pos.y++;
  if (vfb.pos.y > NB_LINE - 1)
    scroll_up();
}

static inline void	vfb_putchar(char c) {
  vfb.buffer[vfb.pos.y * NB_COL + vfb.pos.x] = (vfb.color << 8) | c;
  vfb.pos.x++;
  if (vfb.pos.x == NB_COL)
    new_line();
}

void	vfb_putstr(const char *str, const int size) {
  int	ite;

  for (ite = 0; ite < size; ++ite)
    vfb_putchar(str[ite]);
}

void	vfb_clear() {
  memset(vfb.buffer, 0, 25 * 80 * 2);
  vfb.pos.x = 0;
  vfb.pos.y = 0;
}
