/*
** ck_chans.c for chans in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Wed Jun  1 02:38:46 2016 biteau_j
** Last update Sun Jun  5 21:38:37 2016 biteau_j
*/

# include "join.h"

int	ck_channels(t_fd *current, char **buff, char **chans)
{
  if (current->nbr_chann_joined + tab_size(chans) >= CHANLIMIT)
    return (sprintf(*buff, "405 %s %s :You have joined too many channels\r\n",
		    current->name, chans[0]));
  if (strcmp(chans[0], current->name) == 0)
    return (-1);
  return (0);
}

static char	*get_names(t_fd *current, t_fd *first, char *chan)
{
  t_fd		*tmp;
  char		buff[4096];
  int		ct;

  tmp = first;
  ct = 0;
  sprintf(buff, "353 %s = %s : @", current->name, chan);
  while (tmp)
    {
      ct = -1;
      while (++ct <= tmp->nbr_chann_joined)
	if (strcmp(tmp->chann[ct], chan) == 0)
	  sprintf(buff + strlen(buff), "%s ", tmp->name);
      tmp = tmp->next;
    }
  sprintf(buff + strlen(buff), "\r\n366 %s %s :End of list\r\n",
	  current->name, chan);
  return (strdup(buff));
}

static int	is_valid(char **chans, int ct_chs, int *ret)
{
  if (strlen(chans[ct_chs]) < 2 || (chans[ct_chs][0] != '#' &&
				    chans[ct_chs][0] != '&' &&
				    chans[ct_chs][0] != '+'))
    {
      return (-1);
      *ret = 2;
    }
  return (0);
}

int	ck_valid_chann(char **chans, t_fd *first, t_fd *current, int ct_chs)
{
  int	ret;
  char	*tmp;
  char	msg[4096];

  ret = 0;
  memset(msg, 0, sizeof(msg));
  if (is_valid(chans, ct_chs, &ret) == 0 &&
      strcmp(current->chann[0], chans[ct_chs]) == 0)
    ret = 1;
  else if (already_exists(chans[ct_chs], current->chann_list) == 0)
    {
      add_in_chan(current, chans[ct_chs], current->chann_list);
      ret = 1;
      sprintf(msg, "%s: JOIN :%s\r\n%s", current->name,
	      current->chann[current->nbr_chann_joined - 1],
	      tmp = get_names(current, first,
			      chans[ct_chs]));
      cb_write(current->buff, msg);
      memset(msg, 0, sizeof(msg));
      sprintf(msg, "%s: JOIN :%s\r\n", current->name,
	      current->chann[current->nbr_chann_joined - 1]);
      inform_others(msg, first, current);
      free(tmp);
    }
  return (ret);
}

int		already_exists(char *to_join, t_chann *list)
{
  t_chann	*tmp;

  tmp = list;
  while (tmp)
    {
      if (strcmp(to_join, tmp->name) == 0)
	return (0);
      tmp = tmp->next;
    }
  return (-1);
}
