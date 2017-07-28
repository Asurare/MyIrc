/*
** join.c for join in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 16:49:05 2016 biteau_j
** Last update Sun Jun  5 19:55:42 2016 biteau_j
*/

# include "client.h"

void	join(t_client *cl, char **cmds)
{
  sprintf(cl->buff + strlen(cl->buff), "JOIN");
  if (tab_size(cmds) > 1 && (cmds[1][0] == '#' || cmds[1][0] == '&'))
    {
      sprintf(cl->buff + strlen(cl->buff), " %s", cmds[1]);
      memset(cl->chan, 0, sizeof(cl->chan));
      sprintf(cl->chan, "%s", cmds[1]);
    }
  printf("%s\n", cl->buff);
  sprintf(cl->buff + strlen(cl->buff), "\r\n");
}
