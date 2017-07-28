/*
** users.c for users in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 16:51:11 2016 biteau_j
** Last update Sun Jun  5 16:51:28 2016 biteau_j
*/

# include "client.h"

void	users(t_client *cl, char **cmds)
{
  (void)cmds;
  sprintf(cl->buff + strlen(cl->buff), "USERS\r\n");
}
