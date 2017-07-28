/*
** wstatement.c for statement in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp/src
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat May 14 17:56:13 2016 biteau_j
** Last update Sun May 15 22:32:47 2016 biteau_j
*/

#include "server.h"

void	help(t_server *srv, char **tab)
{
  (void)tab;
  dprintf(srv->client_fd, "214-The following commands are recognized:\r\n");
  dprintf(srv->client_fd, "USER PASS RETR NOOP QUIT CWD STOR LIST DELE\r\n");
  dprintf(srv->client_fd, "HELP PWD PASV PORT CDUP\r\n");
  dprintf(srv->client_fd, "214 Help OK.\r\n");
}

void	quit(t_server *srv, char **tab)
{
  (void)tab;
  dprintf(srv->client_fd, "221 Leaving server.\r\n");
  close(srv->client_fd);
}

void	noop(t_server *srv, char **tab)
{
  (void)tab;
  dprintf(srv->client_fd, "200 Waiting.\r\n");
}
