/*
** get_set_fds.h for fds in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Thu May 26 11:41:39 2016 biteau_j
** Last update Fri Jun  3 12:36:43 2016 biteau_j
*/

#ifndef GET_SET_FDS_H_
# define GET_SET_FDS_H_

# include <stdlib.h>

# include "structure.h"

void	set_fds(t_server **);
int	get_max_fds(t_fd *);

#endif /* GET_SET_FDS_H_ */
