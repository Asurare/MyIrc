/*
** read_write.c for read_write in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 09:57:56 2016 biteau_j
** Last update Sun Jun  5 22:10:04 2016 biteau_j
*/

# include "client.h"

void	read_cmd(t_client *cl)
{
  char	buff[512];
  char	**tab;

  memset(buff, 0, sizeof(buff));
  if (read(0, buff, 512) <= 0)
    perror("Read error");
  tab = str_to_wordtab(buff);
  if (cl->connected == true ||
      strncmp(buff, "/server", strlen("/server")) == 0)
    {
      memset(cl->buff, 0, sizeof(cl->buff));
      do_actions(cl, tab);
      if (cl->run == true)
	write(cl->fd, cl->buff, strlen(cl->buff));
    }
  free_tab(&tab);
}

void	read_srv(t_client *cl)
{
  char	buff[512];

  memset(buff, 0, sizeof(buff));
  if (read(cl->fd, buff, 512) <= 0)
    cl->run = false;
  else
    write(1, buff, strlen(buff));
}

void	write_srv(t_client *cl)
{
  (void)cl;
}
