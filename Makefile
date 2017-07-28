##
## Makefile for my_ls in /home/biteau_j/rendu/PSU_2014_my_ls
##
## Made by Jonathan Biteau
## Login   <biteau_j@epitech.net>
##
## Started on  Mon Nov 24 23:23:48 2014 Jonathan Biteau
## Last update Sun May 15 23:23:16 2016 biteau_j
##

CC	= gcc

RM	= rm -f

DIR	= src/

SRC	= $(DIR)main.c			\
	  $(DIR)str_to_wordtab.c	\
	  $(DIR)functions.c		\
	  $(DIR)init.c			\
	  $(DIR)loop.c			\
	  $(DIR)actions.c		\
	  $(DIR)users.c			\
	  $(DIR)directory_functions.c	\
	  $(DIR)wstatement.c		\
	  $(DIR)data_functions.c	\
	  $(DIR)list.c			\

NAME	= server

OBJ	= $(SRC:.c=.o)

CFLAGS	= -W -Wall -Wextra -Werror -I ./include

$(NAME) : $(OBJ)
	  $(CC) -o $(NAME) $(OBJ)

all :	  $(NAME)

clean :
	  $(RM) $(OBJ)

fclean :  clean
	  $(RM) $(NAME)

re :	  fclean all

.PHONY:	  re clean fclean all
