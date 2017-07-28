/*
** ck_nick.c for ck_nick in /home/biteau_j/rendu/tek2/PSU/PSU_2015_myirc
**
** Made by biteau_j
** Login   <biteau_j@epitech.net>
**
** Started on  Sat Jun  4 17:42:11 2016 biteau_j
** Last update Sat Jun  4 17:45:15 2016 biteau_j
*/

# include "nick.h"

static int	isvalid(char c)
{
  if ((c >= '[' && c <= '`') || (c >= '{' && c <= '}'))
    return (1);
  return (0);
}

int	good_nick(char *name)
{
  int		ct;

  ct = 1;
  if (isalpha(name[0]) == 1 || isvalid(name[0]) == 1)
    {
      while (name[ct])
	{
	  if (!isalpha(name[ct]) && !isdigit(name[ct]) &&
	      !isvalid(name[ct]) && name[ct] != '-')
	    return (-1);
	  ct += 1;
	}
      return (-1);
    }
  return (0);
}
