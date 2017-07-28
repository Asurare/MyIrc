/*
** part.c for part in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Wed Jun  1 10:26:33 2016 biteau_j
** Last update Sun Jun  5 15:06:21 2016 biteau_j
*/

# include "part.h"

static void	get_new_chan(t_fd ****current, char *chan)
{
  int		ct;

  ct = 0;
  while (strcmp((***current)->chann[ct], chan) != 0 &&
	 ct < (***current)->nbr_chann_joined)
    ct += 1;
  while (ct <= (***current)->nbr_chann_joined)
    {
      memset((***current)->chann[ct], 0, CHANNELLEN);
      snprintf((***current)->chann[ct], CHANNELLEN, "%s",
	       (***current)->chann[ct + 1]);
      ct += 1;
    }
}

static void	leave_chann(t_fd ***current, char *chan)
{
  t_chann	*tmp;
  int		ct;

  tmp = (**current)->chann_list;
  ct = 0;
  while (tmp && strcmp(tmp->name, chan) != 0)
    tmp = tmp->next;
  while (tmp->list_of_users[ct])
    {
      if (strcmp(tmp->list_of_users[ct], (char *)(**current)->name) == 0)
	{
	  take_off_from_names(&tmp, (**current)->name);
	  (**current)->nbr_chann_joined -= 1;
	  get_new_chan(&(current), chan);
	  tmp->nbr_of_users -= 1;
	  if (tmp->nbr_of_users == 0)
	    del_chann(&current, &tmp);
	  break;
	}
      ct += 1;
    }
}

static int	find_existing_chan(t_fd **current, char *to_find)
{
  int		ct;

  ct = 0;
  while (ct <= (*current)->nbr_chann_joined)
    {
      if (strcmp((*current)->chann[ct], to_find) == 0)
	return (0);
      ct += 1;
    }
  return  (-1);
}

void	search_channels(t_fd **current, char **chans, t_fd *first, bool quit)
{
  int		ct;
  char		buff[4096];
  char		msg[4096];

  ct = 0;
  memset(buff, 0, sizeof(buff));
  while (chans[ct])
    {
      memset(buff, 0, sizeof(buff));
      if (find_existing_chan(current, chans[ct]) == 0)
	{
	  sprintf(buff + strlen(buff), "%s PART %s\r\n", (*current)->name,
		  chans[ct]);
	  sprintf(msg, "%s PART %s\r\n", (*current)->name, chans[ct]);
	  if (quit == false)
	    inform_others(msg, first, (*current));
	  leave_chann(&current, chans[ct]);
	}
      else
	sprintf(buff + strlen(buff), "403 %s :No such channel.\r\n", chans[ct]);
      ct += 1;
    }
  if (quit == false)
    cb_write((*current)->buff, buff);
  free_tab(&chans);
}

void	part(t_fd *current, t_fd *first, char **cmd)
{
  int	ct;

  ct = 0;
  if (tab_size(cmd) == 1)
    {
      cb_write(current->buff, "461 :Need more params.\r\n");
      return;
    }
  if (cmd[1][0] == ':')
    while (cmd[1][ct])
      {
	cmd[1][ct] = cmd[1][ct + 1];
	ct += 1;
      }
  else
    search_channels(&current, get_params(cmd[1]), first, false);
}
