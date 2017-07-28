/*
** loop.c for loop in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 12 13:13:57 2016 biteau_j
** Last update Sat May 14 16:38:03 2016 biteau_j
*/

#include "server.h"

static int	xaccept(t_server *srv)
{
  if ((srv->client_fd = accept(srv->fd,
			       (struct sockaddr *)&srv->s_in_client,
			       &srv->s_in_size)) == -1)
    {
      perror("Socket error");
      return (EXIT_FAILURE);
    }
  return (0);
}

int	loop(t_server *srv)
{
  char	*client_ip;
  pid_t	pid;
  int	ret;
  char	buff[4096];

    while (42)
    {
      if (xaccept(srv) != 0)
	return (EXIT_FAILURE);
      if ((pid = fork()) == 0)
	{
	  client_ip = inet_ntoa(srv->s_in_client.sin_addr);
	  printf("Connection from %s:%d\n", client_ip, srv->port);
	  dprintf(srv->client_fd, "220 Connected on myFTP server\r\n");
	  while ((ret = read(srv->client_fd, buff, 255)) > 0)
	    {
	      buff[ret] = '\0';
	      actions(srv, buff);
	    }
	  printf("Disconnected from %s:%d\n", client_ip, srv->port);
	  close(srv->fd);
	  exit(EXIT_SUCCESS);
	}
    }
}
