/*
** part.h for part in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Wed Jun  1 13:22:32 2016 biteau_j
** Last update Sat Jun  4 17:13:11 2016 biteau_j
*/

#ifndef PART_H_
# define PART_H_

# include <stdio.h>

# include "str_to_wordtab.h"
# include "structure.h"
# include "actions.h"

/*
**	part.c
*/
void	part(t_fd *, t_fd *, char **);
void	search_channels(t_fd **, char **, t_fd *, bool);

/*
**
*/
void	take_off_from_names(t_chann **, char *);

/*
**	del_chan.c
*/
void	del_chann(t_fd ****, t_chann **);

#endif /* PART_H_ */
