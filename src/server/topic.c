/*
** topic.c for topic in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Wed Jun  1 01:35:08 2016 biteau_j
** Last update Sun Jun  5 18:51:07 2016 biteau_j
*/

# include "topic.h"

static int	snd_part(t_chann *tmp, t_fd *current, char **cmd)
{
  int		ct;
  char		buff[4096];

  ct = 2;
  memset(buff, 0, sizeof(buff));
  if (strcmp(cmd[1], tmp->name) == 0)
    {
      memset(tmp->topic, 0, sizeof(tmp->topic));
      while (cmd[ct] && strlen(tmp->topic) < TOPICLEN)
	sprintf(tmp->topic + strlen(tmp->topic), "%s ", cmd[ct++]);
      sprintf(buff, "332 %s :%s\r\n", tmp->name, tmp->topic);
      cb_write(current->buff, buff);
      return (1);
    }
  return (0);
}

static int	change_topic(t_fd *current, char **cmd)
{
  t_chann	*tmp;
  int		ct;
  int		ret;

  tmp = current->chann_list;
  ct = 0;
  ret = -1;
  while (ct <= current->nbr_chann_joined)
    if (strcmp(cmd[1], current->chann[ct++]) == 0)
      ret = 0;
  if (ret == -1)
    {
      cb_write(current->buff, "442 :You're not on that channel\r\n");
      return (0);
    }
  while (tmp)
    {
      ret += snd_part(tmp, current, cmd);
      tmp = tmp->next;
    }
  return (ret == 0 ? -1 : 0);
}

void	topic(t_fd *current, t_fd *first, char **cmd)
{
  (void)first;
  if (tab_size(cmd) < 2)
    cb_write(current->buff, "461 :Not enough parameters\r\n");
  else
    if (change_topic(current, cmd) == -1)
      cb_write(current->buff, "403 :No such channel\r\n");
}
