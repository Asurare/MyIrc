/*
** functions.c for functions.s in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 13:29:47 2016 biteau_j
** Last update Sun Jun  5 22:46:36 2016 biteau_j
*/

# include "nick.h"

static int	is_already_used(t_fd *first, char *new)
{
  while (first)
    {
      if (strcmp(first->name, new) == 0)
	return (-1);
      first = first->next;
    }
  return (0);
}

static void	user_message(t_fd *client, t_fd *first, char *answer)
{
  inform_others(answer, first, client);
  if (client->logged == true && client->printed == false)
    {
      cb_write(client->buff, "001 Welcome to SuperIRC !\r\n");
      cb_write(client->buff,
	       "002 Your host is babar, running version 1.0\r\n");
      cb_write(client->buff,
	      "003 this server was created few times ago :).\r\n");
      cb_write(client->buff, "004 SuperIRC, v1.0\r\n");
      client->printed = true;
    }
}

static void	change_in_channels(t_fd *client, char *new)
{
  t_chann	*tmp;
  int		ct;

  tmp = client->chann_list;
  while (tmp)
    {
      ct = -1;
      while (tmp->list_of_users[++ct])
	{
	  if (strcmp(tmp->list_of_users[ct], client->name) == 0)
	    tmp->list_of_users[ct] = strdup(new);
	}
      tmp = tmp->next;
    }
}

static void	ck_name(char **cmd, t_fd *client, t_fd *first)
{
  char	answer[512];

  if (good_nick(cmd[1]) == 0)
    {
      sprintf(answer, ":%s!127.0.0.1 NICK %s\r\n", client->name, cmd[1]);
      change_in_channels(client, cmd[1]);
      memset(client->name, 0, sizeof(client->name));
      strncpy(client->name, cmd[1], NICKLEN);
      user_message(client, first, answer);
      if (client->logged == true && client->nick == true)
	cb_write(client->buff, answer);
      client->nick = true;
    }
  else
    cb_write(client->buff, "432 Erroneus nickname\r\n");
}

void	nick(t_fd *client, t_fd *first, char **cmd)
{
  t_fd	*tmp;
  int	ct;

  ct = 0;
  tmp = first;
  if (tab_size(cmd) == 1)
    {
      cb_write(client->buff, "431 No nickname given.\r\n");
      return;
    }
  if (cmd[1][0] == ':')
    while (cmd[1][ct])
      {
	cmd[1][ct] = cmd[1][ct + 1];
	ct += 1;
      }
  if (is_already_used(tmp, cmd[1]))
    cb_write(client->buff, "433 Nickname already in use.\r\n");
  else
    ck_name(cmd, client, first);
}
