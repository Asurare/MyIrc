/*
** connection.c for connection in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/client
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sun Jun  5 09:59:04 2016 biteau_j
** Last update Sun Jun  5 16:45:02 2016 biteau_j
*/

# include "client.h"

static char	*get_ip(char *str)
{
  if (strcmp("localhost", str) == 0)
    return (strdup("127.0.0.1"));
  else
    return (strdup(str));
}

static int	attemp_connection(t_client *cl, char **cmd)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;

  cl->ip = get_ip(cmd[1]);
  if (tab_size(cmd) == 1)
    cl->port = 6667;
  else
    cl->port = atoi(cmd[2]);
  if ((pe = getprotobyname("TCP")) == NULL)
    return (-1);
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(cl->port);
  s_in.sin_addr.s_addr = inet_addr(cl->ip);
  if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      printf("Connection failed.\r\n");
      return (-1);
    }
  cl->fd = fd;
  memset(cl->chan, 0, sizeof(cl->chan));
  cl->connected = true;
  return (0);
}

void	server(t_client *cl, char **cmds)
{
  if (attemp_connection(cl, cmds) == -1)
    return;
  sprintf(cl->buff + strlen(cl->buff), "USER t t t t\r\n");
  sprintf(cl->buff + strlen(cl->buff), "NICK %s\r\n", getenv("LOGNAME"));
}
