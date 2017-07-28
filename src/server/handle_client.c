/*
** fds.c for fds in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 09:33:03 2016 biteau_j
** Last update Sun Jun  5 23:35:08 2016 biteau_j
*/

# include "handle_client.h"

static void	del_elem_snd(t_fd **current, t_fd **tmp)
{
  if ((*tmp) != NULL && (*current)->next == NULL)
    {
      close((*current)->fd);
      (*tmp)->next = NULL;
      cb_destroy((*current)->buff);
      free(*current);
      (*current) = (*tmp);
    }
  else if ((*tmp) != NULL && (*current)->next != NULL)
    {
      close((*current)->fd);
      (*tmp)->next = (*current)->next;
      cb_destroy((*current)->buff);
      free(*current);
      (*current) = (*tmp);
    }
}

static void	del_elem(t_fd **current, t_fd **tmp, t_fd ***list)
{
  printf("Closing connection\n");
  if ((*tmp) == NULL && (*current)->next == NULL)
    {
      close((*current)->fd);
      cb_destroy((**list)->buff);
      free(**list);
      **list = NULL;
    }
  else if ((*tmp) == NULL && (*current)->next != NULL)
    {
      close((*current)->fd);
      *tmp = **list;
      **list = (*current)->next;
      cb_destroy((*tmp)->buff);
      free(*tmp);
      *tmp = NULL;
    }
  else
    del_elem_snd(current, tmp);
}

int	handle_client(t_fd **list, fd_set readfds, t_server *srv)
{
  t_fd	*current;
  t_fd	*tmp;
  char	buff[513];

  current = *list;
  tmp = NULL;
  while (current != NULL)
    {
      if (FD_ISSET(current->fd, &(readfds)))
	{
	  memset(buff, 0, sizeof(buff));
	  if (read(current->fd, buff, 512) == 0 ||
	      split_actions(buff, current, *list, srv) == -1)
	    {
	      del_elem(&current, &tmp, &list);
	      break;
	    }
	}
      if (current != NULL)
	{
	  tmp = current;
	  current = current->next;
	}
    }
  return (*list == NULL ? -1 : 0);
}
