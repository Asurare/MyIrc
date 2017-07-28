/*
** my_str_to_wordtab.c for toto in /home/biteau_j/rendu/tek1
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Wed May 11 15:39:51 2016 biteau_j
** Last update Sat May 14 13:12:21 2016 biteau_j
*/

#include "server.h"

int	tab_size(char **tab)
{
  int	a;
  int	ct;

  a = 0;
  ct = 0;
  while (tab[a])
    {
      if (strlen(tab[a++]) > 0)
	ct++;
    }
  return (ct);
}

char    **str_to_wordtab(char *str)
{
  char	**tab;
  int	i;
  int	j;
  int	k;

  i = 0;
  j = 0;
  k = 0;
  if ((tab = malloc(sizeof(str) * ((strlen(str))))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      if ((tab[k] = malloc(sizeof(str) * strlen(str) + 4)) == NULL)
	return (NULL);
      while ((str[i] == '\r' || str[i] == '\n' || str[i] == ' ') && str[i])
	i += 1;
      j = 0;
      while ((str[i] != '\r' && str[i] != '\n' && str[i] != ' ') && str[i])
	tab[k][j++] = str[i++];
      tab[k][j] = '\0';
      k += 1;
    }
  tab[k] = NULL;
  return (tab);
}
