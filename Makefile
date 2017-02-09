##
## Makefile for wolf in /home/gaby/rendu/gfx_wolf3d/
##
## Made by Gabriel de Blois
## Login   <de-blo_g@epitech.eu>
##
## Started on  Wed Dec  9 00:56:53 2015 Gabriel de Blois
## Last update Thu Feb  9 21:16:46 2017 gaby
##

NAME	=	menger

CC	=	gcc

SRC	=	main.c \
		bmp.c \
		menger.c

CFLAGS	= -Wall -Wextra -Werror -std=gnu99 -O3

OBJ	=	$(SRC:.c=.o)

RM	=	rm -f


all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LIB) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
