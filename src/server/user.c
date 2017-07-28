/*
** user.c for user in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri May 27 01:07:25 2016 biteau_j
** Last update Sat Jun  4 13:04:10 2016 biteau_j
*/

# include <unistd.h>
# include "user.h"

static void	user_message(t_fd *client)
{
  if (client->nick == true)
    {
      cb_write(client->buff, "001 Welcome to SuperIRC !\r\n");
      cb_write(client->buff,
	       "002 Your host is babar, running version 1.0\r\n");
      cb_write(client->buff,
	      "003 this server was created few times ago :).\r\n");
      cb_write(client->buff, "004 SuperIRC, v1.0\r\n");
    }
  client->logged = true;
}

void	user(t_fd *client, t_fd *first, char **cmd)
{
  (void)first;
  if (client->logged == true)
    {
      if (client->printed == true)
	cb_write(client->buff,
		 "462 Unauthorized command (already registered).\r\n");
    }
  else if (tab_size(cmd) < 4 + 1)
    cb_write(client->buff, "461 : Not enough parameters.\r\n");
  else
    user_message(client);
}
