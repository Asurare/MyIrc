/*
** functions.c for functions in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 12 13:39:35 2016 biteau_j
** Last update Sun May 15 23:26:04 2016 biteau_j
*/

#include "server.h"

void	retr(t_server *srv, char **tab)
{
  (void)tab;
  (void)srv;
}

void	stor(t_server *srv, char **tab)
{
  (void)tab;
  (void)srv;
}

void	dele(t_server *srv, char **tab)
{
  char	path[4096];

  if (tab_size(tab) == 1 || realpath(tab[1], path) == NULL ||
      remove(path) == -1)
    dprintf(srv->client_fd, "550 File not found or no access.\r\n");
  else
    dprintf(srv->client_fd, "250 File \"%s\" deleted.\r\n", tab[1]);
}

static void	cwd_l(t_server *srv, char **tab)
{
  char		path[4096];

  if (realpath(tab[1], path) == NULL)
    {
      dprintf(srv->client_fd, "425 File or directory not found.\r\n");
      return;
    }
  chdir(path);
}

void	cdup(t_server *srv, char **tab)
{
  char	*tmp[3] = {"cwd", "..", NULL};

  (void)tab;
  if (strcasecmp(tab[0], "list") == 0)
    cwd_l(srv, tmp);
  else
    cwd(srv, tmp);
}
