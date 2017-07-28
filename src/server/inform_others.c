/*
** inform_others.c for inform_others in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri Jun  3 12:49:33 2016 biteau_j
** Last update Mon Jun  6 10:06:21 2016 biteau_j
*/

# include "actions.h"

static int	xwrite(t_fd *cl, char *msg)
{
  int	ct;

  ct = 0;
  while (msg[ct])
    if (write(cl->fd, &msg[ct++], 1) == -1)
      return (-1);
  return (0);
}

static int	same_chann(t_fd *first, t_fd *current)
{
  int		ct;
  int		cts;

  ct = 0;
  cts = 0;
  while (ct <= current->nbr_chann_joined)
    {
      cts = 0;
      while (cts <= first->nbr_chann_joined)
	{
	  printf("Comparing: %s %s %s %s\n", current->chann[ct], first->chann[cts],
		 current->name, first->name);
	  if (strcmp(current->chann[ct], first->chann[cts]) == 0 &&
	      strcmp(current->name, first->name) != 0 &&
	      strlen(first->chann[cts]) != 0)
	    return (0);
	  cts += 1;
	}
      ct += 1;
    }
  return (-1);
}

void	inform_others(char *msg, t_fd *first, t_fd *current)
{
  t_fd	*tmp;

  tmp = first;
  printf("informing others %s", msg);
  while (tmp)
    {
      if (strcmp(tmp->name, current->name) != 0 && same_chann(first,
							      current) == 0)
	xwrite(tmp, msg);
      tmp = tmp->next;
    }
}
