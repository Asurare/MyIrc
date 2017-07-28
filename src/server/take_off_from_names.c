/*
** take_off_from_names.c for take_off in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 17:08:10 2016 biteau_j
** Last update Sat Jun  4 17:14:02 2016 biteau_j
*/

# include "part.h"

static char	*xstrdup(char *str)
{
  if (str == NULL)
    return (NULL);
  else
    return (strdup(str));
}

static char	**new_list(char **old, char *name)
{
  char		**tab;
  int		ct;
  int		cts;

  ct = 0;
  cts = 0;
  if ((tab = malloc(sizeof(tab) * (tab_size(old) + 1))) == NULL)
    return (NULL);
  while (old[ct])
    {
      if (strcmp(old[ct], name) == 0)
	ct += 1;
      else
	tab[cts++] = xstrdup(old[ct++]);
    }
  tab[cts] = NULL;
  free_tab(&(old));
  return (tab);
}

void	take_off_from_names(t_chann **tmp, char *name)
{
  int		ct;
  int		cts;

  ct = 0;
  cts = 0;
  while ((*tmp)->list_of_users[ct])
    {
      if (strcmp((*tmp)->list_of_users[ct], name) == 0)
	{
	  (*tmp)->list_of_users = new_list((*tmp)->list_of_users, name);
	  return;
	}
      ct += 1;
    }
}
