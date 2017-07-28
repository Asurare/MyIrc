/*
** set_fds.c for set_fds in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 09:56:59 2016 biteau_j
** Last update Sun Jun  5 11:07:52 2016 biteau_j
*/

# include "client.h"

void	set_fds(fd_set *rfd, fd_set *wfd, t_client *cl)
{
  static bool	first;

  FD_ZERO(&(*rfd));
  FD_ZERO(&(*wfd));
  if (first == false)
    {
      cl->fd = 0;
      first = true;
    }
  FD_SET(cl->fd, (cl->read == true ? &(*rfd) : &(*wfd)));
  FD_SET(0, &(*rfd));
}
