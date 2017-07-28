/*
** join_fcts.c for join in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 17:19:00 2016 biteau_j
** Last update Sun Jun  5 23:12:09 2016 biteau_j
*/

# include "join.h"

static int	get_size(t_chann *list)
{
  t_chann	*tmp;
  int		ret;

  ret = 0;
  tmp = list;
  while (tmp)
    {
      ret += strlen(tmp->name);
      tmp = tmp->next;
    }
  return (ret);
}

char	**get_chans_as_tab(t_chann *list)
{
  char		**tab;
  t_chann	*tmp;
  int		size;

  tmp = list;
  size = get_size(list);
  if ((tab = malloc(sizeof(tab) * (size + 1))) == NULL ||
      (tab[0] = malloc(sizeof(tab[0]) * (size + 1))) == NULL ||
      (tab[1] = malloc(sizeof(tab[0]) * (size + 1))) == NULL)
    return (NULL);
  memset(tab[0], 0, size);
  sprintf(tab[0], "PART");
  memset(tab[1], 0, size);
  while (tmp)
    {
      sprintf(tab[1] + strlen(tab[1]), "%s,", tmp->name);
      tmp = tmp->next;
    }
  tab[1][strlen(tab[1]) - 1] = '\0';
  tab[2] = NULL;
  return (tab);
}

void	init_join_vars(int *cts, int *ret, char *buff)
{
  *cts = -1;
  *ret = 0;
  memset(buff, 0, 4096);
}

char	*names_it(t_fd *current, char *name)
{
  t_fd		*tmp;
  char		buff[4096];
  int		ct;

  tmp = current;
  while (tmp)
    {
      ct = 0;
      sprintf(buff, "353 %s = %s : @", current->name, name);
      while (ct <= tmp->nbr_chann_joined)
	if (strcmp(name, tmp->chann[ct++]) == 0)
	  sprintf(buff + strlen(buff), "%s ", tmp->name);
      tmp = tmp->next;
    }
  sprintf(buff + strlen(buff), "\r\n366 %s %s :End of list",
	  current->name, name);
  return (strdup(buff));
}
