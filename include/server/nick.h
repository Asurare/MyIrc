/*
** functions.c for functions in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 12:10:44 2016 biteau_j
** Last update Sat Jun  4 17:43:52 2016 biteau_j
*/

#ifndef NICK_H_
# define  NICK_H_

# define MAX_NAME_LENGTH 9

# include <ctype.h>
# include <string.h>
# include <stdio.h>

# include "structure.h"
# include "str_to_wordtab.h"
# include "actions.h"

/*
**	ck_nick.c
*/
int	good_nick(char *);

/*
**	nick.c
*/
void	nick(t_fd *, t_fd *, char **);

#endif /* NICK_H_ */
