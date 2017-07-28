/*
** users.c for users in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp/src
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri May 13 10:43:36 2016 biteau_j
** Last update Sun May 15 16:38:08 2016 biteau_j
*/

#include "server.h"

void	pass(t_server *srv, char **tab)
{
  int	size;

  if (srv->pass == 0)
    dprintf(srv->client_fd, "332 Need account for login.\r\n");
  else if ((size = tab_size(tab)) != 1 || srv->anon == 0)
    dprintf(srv->client_fd, "530 Login incorrect.\r\n");
  else if (size == 1)
    {
      dprintf(srv->client_fd, "230 Login successful.\r\n");
      srv->logged = 1;
      srv->anon = 0;
    }
  srv->pass = 0;
}

void	user(t_server *srv, char **tab)
{
  srv->anon = 0;
  srv->pass = 0;
  if (srv->logged == 1)
    dprintf(srv->client_fd, "530 Can't change from guest user.\r\n");
  else if (tab_size(tab) == 1)
    dprintf(srv->client_fd, "530 Permission denied.\r\n");
  else
    {
      if (strcasecmp("anonymous", tab[1]) == 0)
	srv->anon = 1;
      srv->pass = 1;
      dprintf(srv->client_fd, "331 Please specify the password.\r\n");
    }
}
