/*
** topic.c for topic in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 17:28:40 2016 biteau_j
** Last update Sun Jun  5 18:53:39 2016 biteau_j
*/

# include "client.h"

void	topic(t_client *cl, char **cmds)
{
  int	a;

  sprintf(cl->buff + strlen(cl->buff), "TOPIC");
  a = 1;
  while (tab_size(cmds) > 0 && cmds[a])
    sprintf(cl->buff + strlen(cl->buff), " %s", cmds[a++]);
  sprintf(cl->buff + strlen(cl->buff), "\r\n");
}
