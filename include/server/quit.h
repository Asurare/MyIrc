/*
** quit.h for quit in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri May 27 14:17:38 2016 biteau_j
** Last update Sun Jun  5 23:03:23 2016 biteau_j
*/

#ifndef QUIT_H_
# define QUIT_H_

# include <stdio.h>
# include <string.h>

# include "structure.h"
# include "str_to_wordtab.h"
# include "part.h"
# include "actions.h"

char	**get_tab(t_fd *);
void	quit(t_fd *, t_fd *, char **);

#endif /* QUIT_H_ */
