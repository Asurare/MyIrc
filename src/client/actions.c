/*
** actions.c for actions in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 16:52:33 2016 biteau_j
** Last update Sun Jun  5 19:24:37 2016 biteau_j
*/

# include "client.h"

static const char	*acts[] =
  {
    "/nick",
    "/server",
    "/list",
    "/join",
    "/part",
    "/users",
    "/names",
    "/msg",
    "/quit",
    "/topic",
    "/announce",
    NULL,
  };

void	(*action[12])(t_client *, char **) =
{
    &nick,
    &server,
    &list,
    &join,
    &part,
    &users,
    &names,
    &msg,
    &quit,
    &topic,
    &announce,
    NULL
  };

void	do_actions(t_client *cl, char **cmds)
{
  int	a;
  int	ret;

  a = 0;
  ret = 0;
  if (cmds[0][0] != '/')
    {
      (action[7](cl, cmds));
      return;
    }
  while (acts[a])
    {
      if (strcasecmp(cmds[0], acts[a]) == 0)
	(action[a])(cl, cmds);
      a += 1;
    }
}
