/*
** main.c<server> for main in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat May 21 19:22:07 2016 biteau_j
** Last update Thu May 26 12:09:12 2016 biteau_j
*/

# include "loop.h"

int		main(int ac, char **av)
{
  t_server	*srv;

  if (ac != 2)
    return (fprintf(stderr, "Usage : ./server port\n"));
  if (init_server(&srv, av[1], 1) == -1)
    {
      close(srv->fd);
      free(srv);
      return (EXIT_FAILURE);
    }
  if (loop(srv) != 0)
    return (EXIT_FAILURE);
  if (close(srv->client_fd) == -1 ||
      close(srv->fd) == -1)
    return (-1);
  return (0);
}
