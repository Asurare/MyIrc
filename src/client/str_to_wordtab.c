/*
** my_str_to_wordtab.c for toto in /home/biteau_j/rendu/tek1
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Wed May 11 15:39:51 2016 biteau_j
** Last update Tue May 31 17:39:15 2016 biteau_j
*/

# include "str_to_wordtab.h"

char	**get_params(char *str)
{
  char		**tab;
  int		len;
  int		ct;
  int		cts;

  ct = 0;
  cts = 0;
  len = 0;
  if (str == NULL)
    return (NULL);
  if ((tab = malloc(sizeof(tab) * (strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[ct])
    {
      if ((tab[len] = malloc(sizeof(tab) * (strlen(str) + 1))) == NULL)
	return (NULL);
      while (str[ct] && str[ct] != ',')
	tab[len][cts++] = str[ct++];
      tab[len++][cts] = '\0';
      ct += (str[ct] == '\0' ? 0 : 1);
      cts = 0;
    }
  tab[len] = NULL;
  return (tab);
}

void	free_tab(char ***tab)
{
  int	ct;

  if (*tab == NULL)
    return;
  ct = tab_size(*tab);
  while (ct >= 0)
    free((*tab)[ct--]);
  free(*tab);
}

int	tab_size(char **tab)
{
  int	a;
  int	ct;

  a = 0;
  ct = 0;
  if (tab ==  NULL)
    return (0);
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
  if ((tab = malloc(sizeof(str) * (strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      if ((tab[k] = malloc(sizeof(str) * (strlen(str) + 1))) == NULL)
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
