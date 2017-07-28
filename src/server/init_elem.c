/*
** init_elem.c for init_elem in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc/src/server
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 17:34:31 2016 biteau_j
** Last update Sat Jun  4 17:41:10 2016 biteau_j
*/

# include "loop.h"

void	init_elem(t_fd **new)
{
  (*new)->next = NULL;
  (*new)->logged = false;
  (*new)->nick = false;
  (*new)->printed = false;
  (*new)->buff = cb_create();
  (*new)->nbr_chann_joined = 0;
  memset((*new)->chann[0], 0, sizeof((*new)->chann));
  memset((*new)->name, 0, sizeof((*new)->name));
}
