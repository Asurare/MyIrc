/*
** main.c for main in /home/biteau_j/test/socket
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Tue May  3 10:37:22 2016 biteau_j
** Last update Fri May 20 17:10:22 2016 biteau_j
*/

#include "server.h"

t_server	*srv;

static int	ck_path(char *path)
{
  DIR		*dir;
  int		ret;

  ret = 0;
  if ((dir = opendir(path)) == NULL)
    return (-1);
  if ((ret = closedir(dir)) == -1)
    {
      perror("Closedir");
      return (ret);
    }
  chdir(path);
  return (0);
}

void	close_fd()
{
  if (close(srv->fd))
    exit(EXIT_FAILURE);
  free(srv->info);
  free(srv);
  printf("\rServer closed.\n");
  exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
  if (ac != 3 || ck_path(av[2]) == -1)
    return (fprintf(stderr, "Usage : ./server port path\n"));
  if (init(&srv, av[1], 1) == -1)
    {
      close(srv->fd);
      free(srv);
      return (EXIT_FAILURE);
    }
  signal(SIGINT, close_fd);
  if (loop(srv) != 0)
    return (EXIT_FAILURE);
  if (close(srv->client_fd) == -1 ||
      close(srv->fd) == -1)
    return (-1);
  free(srv->info);
  free(srv);
  return (0);
}
