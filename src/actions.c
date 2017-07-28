/*
** actions.c for actions in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp/src
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 12 13:54:14 2016 biteau_j
** Last update Fri May 20 16:42:30 2016 biteau_j
*/

#include "server.h"

void		actions(t_server *srv, char *buff)
{
  int		a;
  char		**tab = str_to_wordtab(buff);
  const char	*actions[] = {"USER", "QUIT", "PASS", "STOR", "LIST", "DELE",
			      "HELP", "PWD", "PASV", "PORT", "NOOP", "RETR",
			      "CWD", "CDUP", NULL};
  void		(*acts[15])(t_server *, char **) =
    {&user, &quit, &pass, &stor, &list,
     &dele, &help, &pwd, &pasv, &port,
     &noop, &retr, &cwd, &cdup, NULL};

  a = 0;
  while (actions[a])
    {
      if (strcasecmp(tab[0], actions[a]) == 0)
	{
	  if (a <= 3 || srv->logged == 1)
	    (acts[a])(srv, tab);
	  else
	    dprintf(srv->client_fd, "530 Please login with USER and PASS.\r\n");
	  a = tab_size(tab) - 1;
	  while (a >= 0)
	    free(tab[a--]);
	  free(tab);
	  return;
	}
      a += 1;
    }
  if (tab_size(tab) >= 1 && a == 14)
    dprintf(srv->client_fd, "500 Unknown command.\r\n");
}
