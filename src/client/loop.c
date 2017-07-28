/*
** loop.c for loop in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 09:56:00 2016 biteau_j
** Last update Sun Jun  5 22:10:43 2016 biteau_j
*/

# include "client.h"

t_client	*g_cl;

static void	exit_clt()
{
  printf("\b\bClosing the client.\n");
  free(g_cl->ip);
  free(g_cl);
  exit(0);
}

static void	select_right_fd(t_client *cl, fd_set rfd, fd_set wfd)
{
  if (FD_ISSET(0, &rfd))
    read_cmd(cl);
  else if (FD_ISSET(cl->fd, &rfd))
    read_srv(cl);
  else if (FD_ISSET(cl->fd, &wfd))
    write_srv(cl);
}

void			loop(t_client *cl)
{
  fd_set		rfd;
  fd_set		wfd;

  g_cl = cl;
  signal(SIGINT, exit_clt);
  while (cl->run == true)
    {
      set_fds(&rfd, &wfd, cl);
      if (cl->run == true)
	if (select((cl->fd + 1), &rfd, &wfd, NULL, NULL) == -1)
	  {
	    perror("Select function error");
	    return;
	  }
      if (cl->run == true)
	select_right_fd(cl, rfd, wfd);
    }
  exit_clt();
}
