/*
** names.c for names in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 16:50:27 2016 biteau_j
** Last update Sun Jun  5 16:50:43 2016 biteau_j
*/

# include "client.h"

void	names(t_client *cl, char **cmds)
{
  sprintf(cl->buff + strlen(cl->buff), "NAMES");
  if (tab_size(cmds) > 1)
    sprintf(cl->buff + strlen(cl->buff), "%s", cmds[1]);
  sprintf(cl->buff + strlen(cl->buff), "\r\n");
}
