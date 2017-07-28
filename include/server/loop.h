/*
** loop.h for server in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat May 21 15:47:51 2016 biteau_j
** Last update Sat Jun  4 17:35:56 2016 biteau_j
*/

#ifndef LOOP_H_
# define LOOP_H_

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>

# include "structure.h"
# include "init.h"
# include "get_set_fds.h"
# include "handle_client.h"

/*
**	loop.c
*/
void	free_all();
void	free_fds(t_server **);
int	loop(t_server *);

/*
**	init_elem.c
*/
void	init_elem(t_fd **);

#endif /* LOOP_H_ */
