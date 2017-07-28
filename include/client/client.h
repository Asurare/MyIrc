/*
** client.h for client in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 18:06:56 2016 biteau_j
** Last update Sun Jun  5 19:26:27 2016 biteau_j
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include "str_to_wordtab.h"

typedef struct	s_client
{
  char		*ip;
  int		port;
  int		fd;
  char		buff[512];
  char		chan[310];
  bool		run;
  bool		read;
  bool		connected;
}		t_client;

/*
**	read_write.c
*/
void	write_srv(t_client *);
void	read_srv(t_client *);
void	read_cmd(t_client *);

/*
**	server.c
*/
void	server(t_client *, char **);

/*
**	list.c
*/
void	list(t_client *, char **);

/*
**	join.c
*/
void	join(t_client *, char **);

/*
**	topic.c
*/
void	topic(t_client *, char **);

/*
**	part.c
*/
void	part(t_client *, char **);

/*
**	users.c
*/
void	users(t_client *, char **);

/*
**	announce.c
*/
void	announce(t_client *, char **);

/*
**	quit.c
*/
void	quit(t_client *, char **);

/*
**	actions.c
*/
void	do_actions(t_client *, char **);

/*
**	names.c
*/
void	names(t_client *, char **);

/*
**	loop.c
*/
void	loop(t_client *);

/*
**	msg.c
*/
void	msg(t_client *, char **);

/*
**	nick.c
*/
void	nick(t_client *, char **);

/*
**	set_fds.c
*/
void	set_fds(fd_set *, fd_set *, t_client *);

#endif /* CLIENT_H_ */
