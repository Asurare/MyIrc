/*
** join_channels.c for join in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 17:21:41 2016 biteau_j
** Last update Sun Jun  5 20:04:20 2016 biteau_j
*/

# include "join.h"

static int	not_already_in_chann(t_chann *list, char *name)
{
  int		ct;

  ct = 0;
  if (list == NULL)
    return (0);
  while (list->list_of_users[ct])
    if (strcmp(list->list_of_users[ct++], name) == 0)
      return (-1);
  return (0);
}

void	join_channels(t_fd *cur, t_fd *first, char **cmd)
{
  char		**ch;
  int		cts;
  char		buff[4096];
  int		ret;
  char		*tmp;

  init_join_vars(&cts, &ret, buff);
  if (ck_channels(cur, (char**)&buff, (ch = get_params(cmd[1]))) == 0)
    while (ch[++cts])
      {
	if ((ret = ck_valid_chann(ch, first, cur, cts)) == 0 &&
	    not_already_in_chann(cur->chann_list, cur->chann[0]) == 0)
	  {
	    join_it(cur, cts, cmd, first);
	    sprintf(buff + strlen(buff), "%s: JOIN :%s\r\n%s\r\n", cur->name,
		    cur->chann[cur->nbr_chann_joined - 1],
		    tmp = names_it(cur, ch[cts]));
	    free(tmp);
	  }
	else if (ret != 1)
	  sprintf(buff + strlen(buff), "403 %s %s :No such channel\r\n",
		  cur->name, ch[cts]);
      }
  free_tab(&ch);
  cb_write(cur->buff, buff);
}
