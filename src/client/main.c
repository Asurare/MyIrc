/*
** main.c for main in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat May 21 15:46:12 2016 biteau_j
** Last update Sun Jun  5 16:58:37 2016 biteau_j
*/

#include "client.h"

int	main(void)
{
  t_client	*client;

  if ((client = malloc(sizeof(t_client))) == NULL)
    return (0);
  client->connected = false;
  client->run = true;
  memset(client->buff, 0, sizeof(client->buff));
  client->read = true;
  loop(client);
}
