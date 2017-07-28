/*
** circ_buffer.h for irc in /home/guinau_v/Epitech/PSU/PSU_2015_myirc/include
**
** Made by Vincent Guinaudeau
** Login guinau_v <vincent.guinaudeau@epitech.eu>
**
** Started on  May May 26 13:25:47 2016 Vincent Guinaudeau
** Last update Thu May 26 23:33:40 2016 biteau_j
*/

#ifndef CIRC_BUFFER_H_
# define CIRC_BUFFER_H_

# include <stdlib.h>

# define CIRC_BUFF_SIZE (20 * 1024)

typedef struct	s_circ_buff
{
  int		pos;
  char		buff[CIRC_BUFF_SIZE + 1];
}		t_circ_buff;

t_circ_buff*	cb_create();
int		cb_write(t_circ_buff* buff, char* str);
void		cb_reset(t_circ_buff* buff);
void		cb_destroy(t_circ_buff* buff);

#endif /* CIRC_BUFFER_H_ */
