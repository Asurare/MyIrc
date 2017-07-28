/*
** users.c for users in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 15:58:42 2016 biteau_j
** Last update Sun Jun  5 22:53:38 2016 biteau_j
*/

# include "users.h"

void	users(t_fd *current, t_fd *first, char **cmd)
{
  t_fd	*tmp;

  (void)cmd;
  tmp = first;
  cb_write(current->buff, "392 :UserID Terminal Host\r\n");
  cb_write(current->buff, "393 :");
  while (tmp)
    {
      printf("%s\n", tmp->name);
      cb_write(current->buff, " ");
      cb_write(current->buff, tmp->name);
      tmp = tmp->next;
    }
  cb_write(current->buff, "\r\n394 :End of users\r\n");
}
