/*
** circ_buffer.c for irc in /home/guinau_v/Epitech/PSU/PSU_2015_myirc/src
**
** Made by Vincent Guinaudeau
** Login guinau_v <vincent.guinaudeau@epitech.eu>
**
** Started on  May May 26 13:33:29 2016 Vincent Guinaudeau
** Last update Sat Jun  4 12:00:02 2016 biteau_j
*/

# include "circ_buffer.h"

t_circ_buff	*cb_create()
{
  t_circ_buff	*alloc;

  if ((alloc = malloc(sizeof(t_circ_buff))) == NULL)
    return (NULL);
  alloc->pos = 0;
  alloc->buff[0] = '\0';
  return (alloc);
}

int	cb_write(t_circ_buff* buff, char* str)
{
  int	i;

  i = 0;
  while (str[i] != '\0' && buff->pos + i < CIRC_BUFF_SIZE)
    {
      buff->buff[i + buff->pos] = str[i];
      ++i;
    }
  buff->buff[i + buff->pos] = '\0';
  buff->pos += i;
  return (str[i] == '\0');
}

void	cb_reset(t_circ_buff* buff)
{
  buff->pos = 0;
  buff->buff[0] = '\0';
}

void	cb_destroy(t_circ_buff* buff)
{
  free(buff);
}
