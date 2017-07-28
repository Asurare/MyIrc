/*
** join.h for joiçn in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun May 29 01:55:23 2016 biteau_j
** Last update Sat Jun  4 17:50:11 2016 biteau_j
*/

#ifndef JOIN_H_
# define JOIN_H_

# include <stdio.h>
# include <string.h>

# include "str_to_wordtab.h"
# include "structure.h"
# include "part.h"
# include "names.h"
# include "actions.h"

/*
**	join_channels.c
*/
void	join_channels(t_fd *, t_fd *, char **);

/*
**	join_fcts.c
*/
char	**get_chans_as_tab(t_chann *);
void	init_join_vars(int *, int *, char *);
char	*names_it(t_fd *, char *);

/*
**	join.c
*/
void	join_it(t_fd *, int, char **, t_fd *);
void	join(t_fd *, t_fd *, char **);
int	add_in_chan(t_fd *, char *, t_chann *);
char	*names_it(t_fd *, char *);

/*
**	ck_chans.c
*/
int	ck_channels(t_fd *, char **, char **);
int	ck_valid_chann(char **, t_fd *, t_fd *, int);
int	already_exists(char *, t_chann *);

#endif /* JOIN_H_ */
