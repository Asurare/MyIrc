/*
** actions.h for actions in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 10:38:46 2016 biteau_j
** Last update Sun Jun  5 19:08:38 2016 biteau_j
*/

#ifndef ACTIONS_H_
# define ACTIONS_H_

# include <string.h>
# include <stdio.h>

# include "structure.h"
# include "str_to_wordtab.h"
# include "nick.h"
# include "quit.h"
# include "user.h"
# include "names.h"
# include "msg.h"
# include "list.h"
# include "join.h"
# include "part.h"
# include "topic.h"
# include "users.h"
# include "announce.h"

/*
**	init_actions.c
*/
void	init_start(int *, int *, int *, char *);
void	init_actions(int *, int *, char ***, char *);

/*
**	actions.c
*/
int	split_actions(char *, t_fd *, t_fd *, t_server *);

/*
**	inform_others.c
*/
void	inform_others(char *, t_fd *, t_fd *);

#endif /* ACTIONS_H_ */
