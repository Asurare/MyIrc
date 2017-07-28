/*
** del_chan.c for del in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 17:01:37 2016 biteau_j
** Last update Sun Jun  5 21:48:18 2016 biteau_j
*/

#include "part.h"

static void	del_elem_snd(t_chann ***old, t_chann ***elem)
{
  if ((**old) != NULL && (**elem)->next == NULL)
    {
      (**old)->next = NULL;
      free_tab(&((**elem)->list_of_users));
      free((**elem));
    }
  else if ((**old) != NULL && (**elem)->next != NULL)
    {
      (**old)->next = (**elem)->next;
      free_tab(&((**elem)->list_of_users));
      free((**elem));
      (**elem) = (**old);
    }
}

static void	del_elem(t_chann **elem, t_chann **old, t_fd *****current)
{
  if ((*old) == NULL && (*elem)->next == NULL)
    {
      free_tab(&((****current)->chann_list->list_of_users));
      free((****current)->chann_list);
      (****current)->chann_list = NULL;
    }
  else if ((*old) == NULL && (*elem)->next != NULL)
    {
      *old = (****current)->chann_list;
      (****current)->chann_list = (****current)->chann_list->next;
      free_tab(&((*old)->list_of_users));
      free((*old));
      (*old) = NULL;
    }
  else
    del_elem_snd(&old, &elem);
}

void		del_chann(t_fd ****current, t_chann **tmp)
{
  t_chann	*old;
  t_chann	*a_list;

  old = NULL;
  a_list = (***current)->chann_list;
  while (a_list)
    {
      if (strcmp(a_list->name, (*tmp)->name) == 0)
	{
	  del_elem(&a_list, &old, &current);
	  return;
	}
      if (a_list != NULL && (***current)->chann_list != NULL)
	{
	  old = a_list;
	  a_list = a_list->next;
	}
    }
}
