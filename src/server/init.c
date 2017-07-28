/*
** init.c for init in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 12 13:12:48 2016 biteau_j
** Last update Sun May 29 01:24:19 2016 biteau_j
*/

#include "init.h"

int	init_server(t_server **srv, char *port, int opt)
{
  if (((*srv) = malloc(sizeof(t_server))) == NULL ||
      ((*srv)->port = atoi(port)) == 0 ||
      ((*srv)->pe = getprotobyname("TCP")) == NULL)
    return (-1);
  (*srv)->fd_list = NULL;
  (*srv)->chann_list = NULL;
  (*srv)->s_in_size = sizeof((*srv)->s_in_client);
  (*srv)->s_in.sin_family = AF_INET;
  (*srv)->s_in.sin_port = htons((*srv)->port);
  (*srv)->s_in.sin_addr.s_addr = INADDR_ANY;
  if (((*srv)->fd = socket(AF_INET, SOCK_STREAM, (*srv)->pe->p_proto)) == -1 ||
      (setsockopt((*srv)->fd, SOL_SOCKET, SO_REUSEADDR, &opt,
		  sizeof(int))) == -1 ||
      bind((*srv)->fd, (const struct sockaddr *)&(*srv)->s_in,
	   sizeof((*srv)->s_in)) == -1 ||
      listen((*srv)->fd, 42) == -1)
    {
      perror("Server error");
      return (-1);
    }
  return (0);
}
