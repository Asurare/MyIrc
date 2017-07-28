/*
** data_functions.c for data in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp/src
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun May 15 18:21:14 2016 biteau_j
** Last update Sun May 15 23:37:46 2016 biteau_j
*/

#include "server.h"

static int	init_passive(t_pass_act *info)
{
  int	opt;

  opt = 1;
  if ((info->pe = getprotobyname("TCP")) == NULL)
    return (-1);
  info->s_in_size = sizeof(info->s_in_client);
  info->s_in.sin_family = AF_INET;
  info->s_in.sin_port = 0;
  info->s_in.sin_addr.s_addr = INADDR_ANY;
  if ((info->fd = socket(AF_INET, SOCK_STREAM, info->pe->p_proto)) == -1 ||
      (setsockopt(info->fd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &opt,
		  sizeof(int))) == -1 ||
      bind(info->fd, (const struct sockaddr *)&info->s_in,
	   sizeof(info->s_in)) == -1 ||
      listen(info->fd, 42) == -1)
    {
      perror("Server error");
      return (-1);
    }
  getsockname(info->fd, (struct sockaddr *)&info->s_in, &info->s_in_size);
  return (ntohs(info->s_in.sin_port));
}

void	pasv(t_server *srv, char **tab)
{
  int	port;

  (void)tab;
  port = init_passive(srv->info);
  dprintf(srv->client_fd, "227 Entering passive mode(127,0,0,1,%d,%d)\r\n",
	  port / 256, port % 256);
  srv->info->mode = PASV;
}

void	port(t_server *srv, char **tab)
{
  (void)srv;
  (void)tab;
}
