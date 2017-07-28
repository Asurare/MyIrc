/*
** structure.h for structure in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 10:47:48 2016 biteau_j
** Last update Sun Jun  5 23:01:39 2016 biteau_j
*/

#ifndef STRUCTURE_H_
# define STRUCTURE_H_

# define CHANLIMIT	10
# define NICKLEN	9
# define TOPICLEN	80
# define CHANNELLEN	50
# define AWAYLEN	160

# include <sys/wait.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>

# include "circ_buffer.h"

typedef struct		s_chann
{
  char			name[CHANNELLEN + 1];
  char			key[CHANNELLEN + 1];
  int			nbr_of_users;
  char			**list_of_users;
  char			topic[TOPICLEN + 1];
  struct s_chann	*next;
}			t_chann;

typedef struct	s_fd
{
  int		fd;
  char		chann[CHANLIMIT][CHANNELLEN + 1];
  char		name[NICKLEN + 1];
  bool		logged;
  bool		nick;
  t_circ_buff	*buff;
  bool		printed;
  int		nbr_chann_joined;
  t_chann	*chann_list;
  struct s_fd	*next;
}		t_fd;

typedef struct		s_server
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  struct sockaddr_in	s_in_client;
  socklen_t		s_in_size;
  fd_set		readfds;
  int			port;

  int			fd;
  int			client_fd;

  t_fd			*fd_list;
  t_chann		*chann_list;
}			t_server;

#endif /* STRUCTURE_H_ */
