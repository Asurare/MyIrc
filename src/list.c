/*
** list.c for list in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp/src
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun May 15 23:21:24 2016 biteau_j
** Last update Tue May 17 13:29:23 2016 biteau_j
*/

#include "server.h"

static char	*get_cwd(char *buff)
{
  int	size;

  size = (int)pathconf(".", _PC_PATH_MAX);
  buff = getcwd(buff, size);
  return (buff);
}

static int	ck_fork(int fd, pid_t *pid)
{
  if (((*pid) = fork()) == -1)
    {
      close(fd);
      return (-1);
    }
  return (*pid);
}

static	int	ck_items(t_server *srv, char **tab, char *path)
{
  (void)tab;
  if (srv->info->mode == NONE)
    {
      dprintf(srv->client_fd, "425 Use PORT or PASV first.\r\n");
      return (-1);
    }
  dprintf(srv->client_fd, "150 Data connection.\r\n");
  if (tab_size(tab) > 1 && (chdir(realpath(tab[1], path)) == -1 ||
			    get_cwd(path) == NULL))
    {
      dprintf(srv->client_fd, "501 cannot found.\r\n");
      close(srv->info->client_fd);
      return (-1);
    }
  return (0);
}

void		list(t_server *srv, char **tab)
{
  int	fd;
  pid_t	pid;
  char	path[4096];

  if (ck_items(srv, tab, path) == -1)
    return;
  srv->info->client_fd = accept(srv->info->fd, (struct sockaddr *)
			   &srv->info->s_in_client, &srv->info->s_in_size);
  fd = dup(1);
  dup2(srv->info->client_fd, 1);
  if ((pid = ck_fork(srv->info->client_fd, &pid)) == -1)
    return;
  if (pid == 0)
    execl("/bin/ls", "ls", NULL);
  else
    waitpid(pid, 0, WSTOPPED);
  dup2(fd, 1);
  close(srv->info->client_fd);
  dprintf(srv->client_fd, "226 Closing data connection.\r\n");
  chdir(path);
  srv->info->mode = NONE;
}
