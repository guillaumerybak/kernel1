/*
** string.c for string in /home/champi_f/Kernel/ProjectOne/fromScratch
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Mon Oct 12 14:46:44 2015 Florian Champin
** Last update Mon Oct 12 14:58:22 2015 Florian Champin
*/

void *memset(void *buff, int val, int count)
{
  int i = 0;
  unsigned short *tmp = buff;
  while (i < count)
    {
      tmp[i] = val;
      ++i;
    }
  return buff;
}
