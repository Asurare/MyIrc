/*
** list.c for list in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat May 28 22:05:52 2016 biteau_j
** Last update Sat Jun  4 12:39:49 2016 biteau_j
*/

#include "list.h"

static void	write_in_channels(t_chann *tmp, char **tab, t_fd *current,
				  char	*buff)
{
  int		a;

  a = 0;
  while (tab[a])
    {
      while (tmp)
	{
	  if (strstr(tmp->name, tab[a]) != NULL)
	    {
	      sprintf(buff, "322 %s %d : %s\r\n", current->name,
		      tmp->nbr_of_users, tmp->topic);
	      sprintf(buff + strlen(buff),
		      "323 %s :End of /LIST\r\n", current->name);
	      break;
	    }
	  tmp = tmp->next;
	}
      a += 1;
    }
}

static void	list_specific_channels(t_fd *current, char *args)
{
  char		**tab;
  t_chann	*tmp;
  char		buff[4096];

  tmp = current->chann_list;
  tab = get_params(args);
  memset(buff, 0, sizeof(buff));
  write_in_channels(tmp, tab, current, buff);
  free_tab(&tab);
  cb_write(current->buff, buff);
}

static void	list_all_channels(t_fd *current)
{
  t_chann	*tmp;
  char		buff[4096];

  memset(buff, 0, sizeof(buff));
  tmp = current->chann_list;
  while (tmp)
    {
      sprintf(buff + strlen(buff), "322 %s %d : %s\r\n", tmp->name,
	      tmp->nbr_of_users, tmp->topic);
      tmp = tmp->next;
    }
  sprintf(buff + strlen(buff), "323 %s :End of /LIST\r\n", current->name);
  cb_write(current->buff, buff);
}

void	list(t_fd *current, t_fd *first, char **cmd)
{
  (void)first;
  if (tab_size(cmd) == 1)
    list_all_channels(current);
  else
    list_specific_channels(current, cmd[1]);
}
