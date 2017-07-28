/*
** names.c for names in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat May 28 15:51:26 2016 biteau_j
** Last update Sun Jun  5 18:06:03 2016 biteau_j
*/

#include "names.h"

static void	list_specific_users(char **cmd, t_fd *current, t_fd *first)
{
  char		**tab;
  t_fd		*tmp;
  char		buff[4096];
  int		a;

  tmp = first;
  a = 0;
  tab = get_params(cmd[1]);
  memset(buff, 0, 4096);
  while (tab[a])
    {
      sprintf(buff + strlen(buff), "353 %s = %s : @", current->name, tab[a]);
      while (tmp)
	{
	  if (strcmp(tab[a], tmp->chann[0]) == 0)
	    sprintf(buff + strlen(buff), "%s ", tmp->name);
 	  tmp = tmp->next;
	}
      sprintf(buff + strlen(buff), "\r\n");
      a += 1;
    }
  sprintf(buff + strlen(buff), "366 %s %s :End of list\r\n",
	  current->name, cmd[1]);
  cb_write(current->buff, buff);
  free_tab(&tab);
}

static void	list_users_without_chann(t_fd *users, t_fd *current,
					 char *buff)
{
  sprintf(buff + strlen(buff), "353 %s * * :", current->name);
  while (users)
    {
      if (users->nbr_chann_joined == 0)
	sprintf(buff + strlen(buff), "%s ", users->name);
      users = users->next;
    }
  sprintf(buff + strlen(buff), "\r\n366 %s * :End of list\r\n", current->name);
}

static void	list_all_users(t_fd *current, t_fd *first)
{
  t_chann	*tmp;
  char		buff[4096];
  t_fd		*users;
  int		ct;

  tmp = current->chann_list;
  memset(buff, 0, sizeof(buff));
  while (tmp)
    {
      ct = 0;
      sprintf(buff + strlen(buff), "353 %s = : @", tmp->name);
      while (tmp->list_of_users[ct])
	sprintf(buff + strlen(buff), "%s ", tmp->list_of_users[ct++]);
      sprintf(buff + strlen(buff), "\r\n");
      tmp = tmp->next;
    }
  list_users_without_chann(users = first, current, buff);
  cb_write(current->buff, buff);
}

void	names(t_fd *current, t_fd *first, char **cmd)
{
  if (tab_size(cmd) == 1)
    list_all_users(current, first);
  else
    list_specific_users(cmd, current, first);
}
