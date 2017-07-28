##
## Makefile for my_ls in /home/biteau_j/rendu/PSU_2014_my_ls
## 
## Made by Jonathan Biteau
## Login   <biteau_j@epitech.net>
## 
## Started on  Mon Nov 24 23:23:48 2014 Jonathan Biteau
## Last update Sun Jun  5 19:27:50 2016 biteau_j
##

CC	=	clang

RM	=	rm -f

CFLAGS	=	-W -Wall -Wextra -Werror -I ./include/server -I ./include/client -g3

SERVER	=	server

CLIENT	= 	client

DCLIENT	=	src/client/

DSERVER	=	src/server/

SRCSC	=	$(DCLIENT)main.c		\
		$(DCLIENT)str_to_wordtab.c	\
		$(DCLIENT)read_write.c		\
		$(DCLIENT)set_fds.c		\
		$(DCLIENT)loop.c		\
		$(DCLIENT)server.c		\
		$(DCLIENT)nick.c		\
		$(DCLIENT)msg.c			\
		$(DCLIENT)actions.c		\
		$(DCLIENT)announce.c		\
		$(DCLIENT)join.c		\
		$(DCLIENT)list.c		\
		$(DCLIENT)names.c		\
		$(DCLIENT)part.c		\
		$(DCLIENT)quit.c		\
		$(DCLIENT)users.c		\
		$(DCLIENT)topic.c		\

SRCSS	=	$(DSERVER)main.c		\
		$(DSERVER)init.c		\
		$(DSERVER)loop.c		\
		$(DSERVER)handle_client.c	\
		$(DSERVER)actions.c		\
		$(DSERVER)str_to_wordtab.c	\
		$(DSERVER)get_set_fds.c		\
		$(DSERVER)user.c		\
		$(DSERVER)nick.c		\
		$(DSERVER)quit.c		\
		$(DSERVER)names.c		\
		$(DSERVER)part.c		\
		$(DSERVER)announce.c		\
		$(DSERVER)msg.c			\
		$(DSERVER)list.c		\
		$(DSERVER)join.c		\
		$(DSERVER)topic.c		\
		$(DSERVER)free_all.c		\
		$(DSERVER)ck_chans.c		\
		$(DSERVER)inform_others.c	\
		$(DSERVER)users.c		\
		$(DSERVER)ck_nick.c		\
		$(DSERVER)del_chan.c		\
		$(DSERVER)join_channels.c	\
		$(DSERVER)init_elem.c		\
		$(DSERVER)init_actions.c 	\
		$(DSERVER)join_fcts.c		\
		$(DSERVER)take_off_from_names.c	\
		src/circ_buffer.c

OBJSS	=	$(SRCSS:.c=.o)

OBJSC	=	$(SRCSC:.c=.o)

all :		$(OBJSS) $(OBJSC)
		$(CC) -o $(SERVER) $(OBJSS)
		$(CC) -o $(CLIENT) $(OBJSC)

server :	$(OBJSS)
		$(CC) -o $(SERVER) $(OBJSS)

client :	$(OBJSC)
		$(CC) -o $(CLIENT) $(OBJSC)

clean :
		$(RM) $(OBJSS) $(OBJSC)

git-list:
	@git ls-tree -rt HEAD | cut -f 2 | sed -ne "s/SDL.*\.h//;t;p" | sed -e "s/[^\/]*\//    /g"

fclean :	clean
		$(RM) $(SERVER) $(CLIENT)

re :		fclean all

.PHONY:		all clean fclean re
