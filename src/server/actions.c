/*
** fds.c for fds in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 09:30:50 2016 biteau_j
** Last update Mon Jun  6 10:17:14 2016 biteau_j
*/

# include "actions.h"

static void	merge_channels(t_fd *first, t_chann *list)
{
  t_fd		*tmp;

  tmp = first;
  printf("merging\n");
  while (tmp)
    {
      tmp->chann_list = list;
      tmp = tmp->next;
    }
}

static const char	*cmds[] =
  {
    "NICK",
    "USER",
    "QUIT",
    "NAMES",
    "PRIVMSG",
    "LIST",
    "JOIN",
    "TOPIC",
    "PART",
    "USERS",
    "ANNOUNCE",
    NULL
  };

void		(*acts[12])(t_fd *, t_fd *, char **) =
{
  &nick,
  &user,
  &quit,
  &names,
  &msg,
  &list,
  &join,
  &topic,
  &part,
  &users,
  &announce,
  NULL
};

static int	first_part(t_fd *client, t_fd *first, char **tab, int a)
{
  int		ret;

  ret = 0;
  if (a <= 2 || (client->logged == true && client->nick == true))
    {
      (acts[a])(client, first, tab);
      ret = (a == 2 ? -1 : 1);
    }
  return (ret);
}

static int	actions(char *buff, t_fd *client, t_fd *first, t_server *srv)
{
  int		a;
  int		ret;
  char		**tab;
  char		tmp[CIRC_BUFF_SIZE];

  init_actions(&a, &ret, &tab, buff);
  memset(tmp, 0, sizeof(tmp));
  while (cmds[a])
    {
      if (strcasecmp(tab[0], cmds[a]) == 0)
	{
	  if ((ret = first_part(client, first, tab, a)) == 0)
	    sprintf(tmp + strlen(tmp), "451 You're not register.\r\n");
	  srv->chann_list = ((a == 6 || a == 8 || a == 2) ?
			     client->chann_list : srv->chann_list);
	  merge_channels(first, srv->chann_list);
	  break;
	}
      a += 1;
    }
  if (tab_size(tab) >= 1 && a == tab_size((char **)cmds))
    sprintf(tmp + strlen(tmp), "421 %s: Unknown command.\r\n", tab[0]);
  cb_write(client->buff, tmp);
  free_tab(&tab);
  return (ret);
}

static int	xwrite(t_fd *cl)
{
  int	ct;

  ct = 0;
  while (cl->buff->buff[ct])
    if (write(cl->fd, &cl->buff->buff[ct++], 1) == -1)
      return (-1);
  return (0);
}

int	split_actions(char *buff, t_fd *client, t_fd *first, t_server *srv)
{
  int	a;
  int	ct;
  char	tmp[4096];
  int	ret;

  init_start(&a, &ret, &ct, tmp);
  printf("buff: %s\n", buff);
  memset(tmp, 0, sizeof(tmp));
  while (buff[++a])
    {
      while (buff[a] && buff[a + 1] && buff[a] != '\r' && buff[a + 1] != '\n')
	tmp[ct++] = buff[a++];
      if (ct > 0)
	{
	  tmp[ct++] = buff[a++];
	  if (actions(tmp, client, first, srv) == -1)
	    ret = -1;
	  if (client->buff->pos > 0)
	    xwrite(client);
	  cb_reset(client->buff);
	  memset(tmp, 0, sizeof(tmp));
	  ct = 0;
	}
    }
  return (ret);
}
