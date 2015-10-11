/*
** printk.c for printk in /home/champi_f/Kernel/ProjectOne/fromScratch/src
** 
** Made by Florian Champin
** Login   <champi_f@champi-f>
** 
** Started on  Sat Oct 10 11:22:35 2015 Florian Champin
** Last update Sat Oct 10 12:20:32 2015 Florian Champin
*/

#define WHITE_TXT 0x07

void		clear_screen();
unsigned int	printk(char *, unsigned int);

unsigned int	printk(char *message, unsigned int line)
{
  char		*vidmem = (char *) 0xb8000;
  unsigned int	i = 0;

  i = (line * 80 * 2);

  while (*message != 0)
    {
      if (*message == '\n')
	{
	  line++;
	  i = (line * 80 * 2);
	  *message++;
	}
      else
	{
	  vidmem[i] = *message;
	  *message++;
	  vidmem[i] = WHITE_TXT;
	  ++i;
	}
    }
  return (1);
}

void		clear_screen()
{
  char		*vidmem = (char *) 0xb8000;
  unsigned int	i = 0;
  while (i < (80*25*2))
    {
      vidmem[i] = ' ';
      ++i;
      vidmem[i] = WHITE_TXT;
      ++i;
    };
};

int	main()
{
  clear_screen();
  printk("Test\nTest01", 0);
  return (0);
}
