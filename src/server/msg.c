/*
** msg.c for msg in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat May 28 19:54:15 2016 biteau_j
** Last update Sun Jun  5 22:01:26 2016 biteau_j
*/

#include "msg.h"

static int	send_to_user(char *user, t_fd *current, t_fd *first,
			     char **msg)
{
  t_fd		*tmp;
  int		ct;
  char		buff[4096];
  int		ret;

  tmp = first;
  ret = -1;
  while (tmp)
    {
      ct = 2;
      if (strcmp(user, tmp->name) == 0)
	{
	  ret = 0;
	  memset(buff, 0, sizeof(buff));
	  sprintf(buff, ":%s!@srv my_ric PRIVMSG %s :",
		  current->name, tmp->name);
	  while (msg[ct])
	    sprintf(buff + strlen(buff), "%s ", msg[ct++]);
	  sprintf(buff + strlen(buff), "\r\n");
	  write(tmp->fd, buff, strlen(buff));
	}
      tmp = tmp->next;
    }
  return (ret);
}

static int	get_channel(char **msg , int ct, char *buff, t_fd *tmp)
{
  while (msg[ct])
    sprintf(buff + strlen(buff), "%s ", msg[ct++]);
  sprintf(buff + strlen(buff), "\r\n");
  write(tmp->fd, buff, strlen(buff));
  return (0);
}

static int	send_to_channel(char *channel, t_fd *current, t_fd *first,
				char **msg)
{
  t_fd		*tmp;
  int		ct;
  char		buff[4096];
  int		ret;
  int		cts;

  tmp = first;
  ret = -1;
  cts = -1;
  while (tmp)
    {
      ct = 2;
      cts = -1;
      while (++cts <= tmp->nbr_chann_joined)
	if (strcmp(channel, tmp->chann[cts]) == 0)
	  {
	    memset(buff, 0, sizeof(buff));
	    sprintf(buff, ":%s!@srv my_irc PRIVMSG %s :",
		    current->name, tmp->chann[cts]);
	    ret = get_channel(msg, ct, buff, tmp);
	  }
      tmp = tmp->next;
    }
  return (ret);
}

static void	send_msg_to_params(char *params, t_fd *current, t_fd *first,
				   char **msg)
{
  char		**tab;
  int		a;
  char		buff[4096];
  int		ret;

  tab = get_params(params);
  a = 0;
  memset(buff, 0, sizeof(buff));
  while (tab[a])
    {
      if (tab[a][0] == '#' || tab[a][0] == '&' || tab[a][0] == '+')
	ret = send_to_channel(tab[a], current, first, msg);
      else
	ret = send_to_user(tab[a], current, first, msg);
      if (ret == -1)
	sprintf(buff, "401 %s %s :No such nick/channel\r\n", current->name,
		(strcmp(tab[a], "[") == 0 ? " " : tab[a]));
      a += 1;
    }
  cb_write(current->buff, buff);
  free_tab(&tab);
}

void	msg(t_fd *current, t_fd *first, char **cmd)
{
  int	ct;

  ct = 0;
  if (tab_size(cmd) == 2)
    {
      cb_write(current->buff, "412 :No text to send\r\n");
      return;
    }
  if (tab_size(cmd) > 1 && cmd[2][0] == ':')
    while (cmd[2][ct])
      {
	cmd[2][ct] = cmd[1][ct + 1];
	ct += 1;
      }
  if (tab_size(cmd) >= 3)
    send_msg_to_params(cmd[1], current, first, cmd);
  else
    cb_write(current->buff, "411 :No recipient given (PRIVMSG)\r\n");
}
