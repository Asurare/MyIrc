/*
** free_all.c for free in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri Jun  3 01:45:54 2016 biteau_j
** Last update Sun Jun  5 23:11:32 2016 biteau_j
*/

# include "loop.h"

void	free_fds(t_server **tmp)
{
  t_fd		*fd_tmp;
  t_fd		*first;

  first = (*tmp)->fd_list;
  write(1, "caca", 4);
  while ((*tmp)->fd_list)
    {
      printf("caca");
      fd_tmp = (*tmp)->fd_list;
      search_channels(&(fd_tmp), get_tab(fd_tmp), first, true);
      (*tmp)->fd_list = (*tmp)->fd_list->next;
      free(fd_tmp);
    }
}
