/*
** join.c for join in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/include
**
** Made by biteau_j
** Login   <biteau_j@epitech net>
**
** Started on  Sat May 28 19:47:47 2016 biteau_j
** Last update Sun Jun  5 20:04:51 2016 biteau_j
*/

# include "join.h"

int	add_in_chan(t_fd *current, char *name, t_chann *list)
{
  int		ct;

  ct = 0;
  snprintf(current->chann[current->nbr_chann_joined], CHANNELLEN, "%s", name);
  current->nbr_chann_joined++;
  while (list->list_of_users[ct] != NULL)
    ct += 1;
  if ((list->list_of_users[ct] = malloc(sizeof(list->list_of_users[ct]) *
					strlen(current->name) + 1))
      == NULL)
    return (-1);
  sprintf(list->list_of_users[ct], "%s", current->name);
  list->nbr_of_users += 1;
  list->list_of_users[ct + 1] = NULL;
  return (0);
}

static void	add_in_list(t_fd *current, char *name, char *keys)
{
  t_chann	*new;
  t_chann	*tmp;

  tmp = current->chann_list;
  if ((new = malloc(sizeof(t_chann))) == NULL)
    return;
  memset(new->name, 0, sizeof(new->name));
  memset(new->key, 0, sizeof(new->key));
  memset(new->topic, 0, sizeof(new->topic));
  snprintf(current->chann[current->nbr_chann_joined], CHANNELLEN, "%s", name);
  current->nbr_chann_joined++;
  strncpy(new->name, name, CHANNELLEN);
  new->nbr_of_users = 1;
  new->list_of_users = get_params(current->name);
  sprintf(new->key, "%s", (keys == NULL ? keys : ""));
  new->next = NULL;
  if (current->chann_list != NULL)
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
    }
  else
    current->chann_list = new;
}

void	join_it(t_fd *current, int ct_chs, char **cmd, t_fd *first)
{
  char		**keys;
  char		**chans;
  char		msg[4096];

  chans = get_params(cmd[1]);
  if (ct_chs > tab_size(keys = get_params(cmd[2])) || cmd[2] == NULL)
    add_in_list(current, chans[ct_chs], NULL);
  else if (cmd[2] != NULL)
    add_in_list(current, chans[ct_chs], keys[ct_chs]);
  memset(msg, 0, sizeof(msg));
  sprintf(msg, "%s: JOIN :%s\r\n", current->name,
	  current->chann[current->nbr_chann_joined - 1]);
  inform_others(msg, first, current);
  free_tab(&keys);
  free_tab(&chans);
}

void	join(t_fd *current, t_fd *first, char **cmd)
{
  char	**tab;
  int	ct;

  ct = 0;
  if (tab_size(cmd) == 1)
    {
      cb_write(current->buff, "461 JOIN :Not enough parameters\r\n");
      return;
    }
  if (cmd[1][0] == ':')
    while (cmd[1][ct])
      {
	cmd[1][ct] = cmd[1][ct + 1];
	ct += 1;
      }
  if (tab_size(cmd) >= 2 && strcmp(cmd[1], "0") == 0)
    {
      part(current, first, (tab = get_chans_as_tab(current->chann_list)));
      free_tab(&tab);
    }
  else if (tab_size(cmd) >= 2)
    join_channels(current, first, cmd);
  printf("%s:%s\n", current->name, current->chann_list->name);
}
