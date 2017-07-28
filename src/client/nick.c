/*
** nick.c for nick in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 16:43:59 2016 biteau_j
** Last update Sun Jun  5 16:44:13 2016 biteau_j
*/

# include "client.h"

void	nick(t_client *cl, char **cmds)
{
  sprintf(cl->buff + strlen(cl->buff), "NICK");
  if (tab_size(cmds) > 1)
    sprintf(cl->buff + strlen(cl->buff), " %s", cmds[1]);
  sprintf(cl->buff + strlen(cl->buff), "\r\n");
}
