/*
** quit.c for quit in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 16:51:53 2016 biteau_j
** Last update Sun Jun  5 19:39:52 2016 biteau_j
*/

# include "client.h"

void	quit(t_client *cl, char **cmds)
{
  int	a;

  a = 1;
  sprintf(cl->buff + strlen(cl->buff), "QUIT");
  while (tab_size(cmds) > 1 && cmds[a])
    sprintf(cl->buff + strlen(cl->buff), " %s", cmds[a++]);
  sprintf(cl->buff + strlen(cl->buff), "\r\n");
  cl->run = false;
}
