/*
** directory_functions.c for directory in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp/src
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri May 13 11:16:31 2016 biteau_j
** Last update Sun May 15 23:21:49 2016 biteau_j
*/

#include "server.h"

void	pwd(t_server *srv, char **tab)
{
  char	*buff;
  int	size;

  (void)tab;
  buff = NULL;
  size = (int)pathconf(".", _PC_PATH_MAX);
  buff = getcwd(buff, size);
  dprintf(srv->client_fd, "257 \"%s\"\r\n", buff);
  free(buff);
}

char	*get_cwd(char *buff)
{
  int	size;

  size = (int)pathconf(".", _PC_PATH_MAX);
  buff = getcwd(buff, size);
  return (buff);
}

void	cwd(t_server *srv, char **tab)
{
  char	path[4096];

  if (tab_size(tab) == 1)
    {
      dprintf(srv->client_fd, "550 Failed to change directory.\r\n");
      return;
    }
  if (realpath(tab[1], path) == NULL)
    {
      dprintf(srv->client_fd, "550 Failed to change directory.\r\n");
      return;
    }
  chdir(path);
  dprintf(srv->client_fd, "250 Directory successfully changed.\r\n");
}
