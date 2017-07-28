/*
** init_actions.c for actiçons in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 17:46:20 2016 biteau_j
** Last update Sat Jun  4 17:49:19 2016 biteau_j
*/

# include "actions.h"

void	init_start(int *a, int *ret, int *ct, char *tmp)
{
  *a = -1;
  *ret = 0;
  *ct = 0;
  memset(tmp, 0, 4096);
}

void	init_actions(int *a, int *ret, char ***tab, char *buff)
{
  *a = 0;
  *ret = 0;
  *tab = str_to_wordtab(buff);
}
