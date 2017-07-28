/*
** get_set_fds.c for fds in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 11:40:18 2016 biteau_j
** Last update Fri May 27 16:09:33 2016 biteau_j
*/

# include "get_set_fds.h"

void	set_fds(t_server **srv)
{
  t_fd	*loc;

  loc = (*srv)->fd_list;
  while (loc)
    {
      FD_SET(loc->fd, &((*srv)->readfds));
      loc = loc->next;
    }
}

int	get_max_fds(t_fd *list)
{
  int	tmp;
  t_fd	*loc;

  if (list == NULL)
    return (0);
  loc = list;
  tmp = 0;
  while (loc)
    {
      loc->fd > tmp ? tmp = loc->fd : tmp;
      loc = loc->next;
    }
  return (tmp == 0 ? 0 : tmp + 1);
}
