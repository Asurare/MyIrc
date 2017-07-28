/*
** msg.c for msg in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 16:42:46 2016 biteau_j
** Last update Sun Jun  5 17:20:52 2016 biteau_j
*/

# include "client.h"

void	msg(t_client *cl, char **cmds)
{
  int	a;

  sprintf(cl->buff + strlen(cl->buff), "PRIVMSG");
  a = 2;
  if (cmds[0][0] != '/')
    {
      a = 0;
      if (strlen(cl->chan) > 0)
	sprintf(cl->buff + strlen(cl->buff), " %s", cl->chan);
      else
	sprintf(cl->buff + strlen(cl->buff), " [");
    }
  else if (tab_size(cmds) > 1)
    sprintf(cl->buff + strlen(cl->buff), " %s", cmds[1]);
  while (tab_size(cmds) > 0 && cmds[a])
    sprintf(cl->buff + strlen(cl->buff), " %s", cmds[a++]);
  sprintf(cl->buff + strlen(cl->buff), "\r\n");
}
