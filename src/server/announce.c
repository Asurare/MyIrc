/*
** announce.c for announce in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 18:56:14 2016 biteau_j
** Last update Sun Jun  5 19:34:46 2016 biteau_j
*/

# include "announce.h"

void	announce(t_fd *current, t_fd *first, char **cmd)
{
  char	buff[512];
  int	a;
  t_fd	*tmp;

  a = 1;
  tmp = first;
  memset(buff, 0, sizeof(buff));
  printf("announce function\r\n");
  if (tab_size(cmd) < 2)
    cb_write(current->buff, "412 No text to send\r\n");
  else
    {
      sprintf(buff + strlen(buff), "!General announce by %s: ", current->name);
      while (cmd[a])
	sprintf(buff + strlen(buff), "%s ", cmd[a++]);
    }
  sprintf(buff + strlen(buff), "\r\n");
  while (tmp)
    {
      write(tmp->fd, buff, strlen(buff));
      tmp = tmp->next;
    }
}
