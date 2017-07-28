/*
** server.h for server in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myftp/sserver
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri May  6 10:11:53 2016 biteau_j
** Last update Sun May 15 21:47:44 2016 biteau_j
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <sys/wait.h>

enum			e_types
  {
    NONE,
    PASV,
    ACT
  };

typedef struct		s_pass_act
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  struct sockaddr_in	s_in_client;
  int			client_fd;
  int			port;
  socklen_t		s_in_size;
  int			fd;
  enum e_types		mode;
}			t_pass_act;

typedef struct		s_server
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  struct sockaddr_in	s_in_client;

  int			fd;
  int			client_fd;
  int			port;
  socklen_t		s_in_size;
  int			pass;
  int			logged;
  int			anon;
  struct s_pass_act	*info;
}			t_server;

/*
**	str_to_wordtab.c
*/
char	**str_to_wordtab(char *);
int	tab_size(char **tab);

/*
**	loop.c
*/
int	loop(t_server *);

/*
**	init.c
*/
int	init(t_server **srv, char *port, int opt);

/*
**	functions.c
*/
void	retr(t_server *srv, char **tab);
void	stor(t_server *srv, char **tab);
void	dele(t_server *srv, char **tab);
void	pasv(t_server *srv, char **tab);
void	port(t_server *srv, char **tab);
void	cdup(t_server *srv, char **tab);

/*
**	actions.c
*/
void	actions(t_server *srv, char *buff);

/*
**	users.c
*/
void	pass(t_server *srv, char **tab);
void	user(t_server *srv, char **tab);

/*
**	directory_functions.c
*/
void	list(t_server *srv, char **tab);
void	pwd(t_server *srv, char **tab);
void	cwd(t_server *srv, char **tab);

/*
**	wstatement.c
*/
void	help(t_server *srv, char **tab);
void	quit(t_server *srv, char **tab);
void	noop(t_server *srv, char **tab);


#endif /* SERVER_H_ */
