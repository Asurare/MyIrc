/*
** quit.c for quit in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Fri May 27 14:12:17 2016 biteau_j
** Last update Sun Jun  5 22:59:51 2016 biteau_j
*/

# include "quit.h"

char	**get_tab(t_fd *current)
{
  char		**tab;
  int		ct;

  ct = 0;
  if ((tab = malloc(sizeof(tab) * (current->nbr_chann_joined + 1))) == NULL)
    return (NULL);
  while (ct < current->nbr_chann_joined)
    {
      printf("%d\n", ct);
      tab[ct] = strdup(current->chann[ct]);
      ct += 1;
    }
  tab[ct] = NULL;
  return (tab);
}

static void	snd(t_fd *current, t_fd *first, char **cmd, char *buff)
{
  char		msg[4096];
  int		a;

  sprintf(buff + strlen(buff), "\r\n");
  cb_write(current->buff, buff);
  memset(buff, 0, AWAYLEN + 1);
  a = 1;
  if (tab_size(cmd) >= 1)
    while (cmd[a])
      sprintf(buff + strlen(buff), "%s ", cmd[a++]);
  memset(msg, 0, sizeof(msg));
  sprintf(msg, "%s QUIT :Quit: %s\r\n", current->name, buff);
  inform_others(msg, first, current);
  search_channels(&current, get_tab(current), first, true);
}

void	quit(t_fd *current, t_fd *first, char **cmd)
{
  int	a;
  char	buff[AWAYLEN + 1];

  a = 0;
  memset(buff, 0, sizeof(buff));
  sprintf(buff, "%s exiting the server :", current->name);
  if (tab_size(cmd) > 1)
    {
      if (cmd[1][0] == ':')
	while (cmd[1][a])
	  {
	    cmd[1][a] = cmd[1][a + 1];
	    a += 1;
	  }
      a = 1;
      while (cmd[a])
	sprintf(buff + strlen(buff), "%s ", cmd[a++]);
    }
  snd(current, first, cmd, buff);
}
