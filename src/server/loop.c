/*
** loop.c for loop in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 12 13:13:57 2016 biteau_j
** Last update Sun Jun  5 23:09:09 2016 biteau_j
*/

# include "loop.h"

t_server	*g_srv;

static int	ck_accept(t_server *srv)
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

static int	add_in_end(t_fd **old, char *ip, int fd, t_server **srv)
{
  t_fd		*list;
  t_fd		*new;

  printf("New connection from: %s\n", ip);
  if (!(new = malloc(sizeof(t_fd))))
    return (-1);
  init_elem(&new);
  new->fd = fd;
  new->chann_list = (*srv)->chann_list;
  list = *old;
  if (*old == NULL)
    *old = new;
  else
    {
      while (list->next != NULL)
	list = list->next;
      list->next = new;
    }
  return (0);
}

void		free_all()
{
  t_chann	*chann_tmp;
  t_server	*tmp;

  tmp = g_srv;
  free_fds(&tmp);
  tmp = g_srv;
  while (tmp->chann_list)
    {
      chann_tmp = tmp->chann_list;
      if (chann_tmp->list_of_users)
	free_tab(&(chann_tmp->list_of_users));
      tmp->chann_list = tmp->chann_list->next;
      free(chann_tmp);
    }
  free(g_srv->fd_list);
  if (g_srv->chann_list)
    free(g_srv->chann_list);
  free(g_srv);
  printf("\rServer irc closed.\n");
  exit(EXIT_SUCCESS);
}

static void	init_vars(t_server *srv, int *ret)
{
  g_srv = srv;
  ck_accept(srv);
  add_in_end(&(srv->fd_list), inet_ntoa(srv->s_in_client.sin_addr),
	     srv->client_fd, &srv);
  *ret = 0;
}

int	loop(t_server *srv)
{
  int			ret;

  signal(SIGINT, free_all);
  init_vars(srv, &ret);
  while (ret != -1)
    {
      FD_ZERO(&(srv->readfds));
      FD_SET(srv->fd, &(srv->readfds));
      set_fds(&srv);
      if (srv->fd_list != NULL)
	if ((ret = select(get_max_fds(srv->fd_list), &(srv->readfds),
			  NULL, NULL, NULL)) == -1)
	  perror("Select function error");
      if ((FD_ISSET(srv->fd, &(srv->readfds)) && ret != -1) ||
	  handle_client(&(srv->fd_list), srv->readfds, srv) == -1)
	{
	  ck_accept(srv);
	  add_in_end(&(srv->fd_list), inet_ntoa(srv->s_in_client.sin_addr),
		     srv->client_fd, &srv);
	}
    }
  return (0);
}
