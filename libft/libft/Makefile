# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 16:28:28 by galy              #+#    #+#              #
#    Updated: 2018/03/09 20:32:04 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
FLAGS	= -Wall -Wextra -Werror

SRCDIR	= .
OBJDIR	= .
INCDIR	= .

####COLOR-SET####

CRESET		=	\033[0m
CRED		=	\033[31m
CGREEN		=	\033[32;5m
CYELLOW		=	\033[33m
CYELLOW+	=	\033[33;1m
CBLUE		=	\033[34m
CMAGENTA	=	\033[35m
CCYAN		=	\033[36m
CWHITE		=	\033[37m

####CURSOR-SET####
CUR_SVE		=	\033[s
CUR_RST		=	\033[u
CUR_CLR		=	\033[K

SRC		= \
	ft_isalpha.c    ft_memccpy.c    ft_memset.c     ft_putnbr_fd.c\
	ft_strcmp.c     ft_striteri.c   ft_strncat.c    ft_strrchr.c\
	ft_isascii.c    ft_memchr.c     ft_putchar.c    ft_putstr.c\
	ft_toupper.c    ft_strcpy.c     ft_strjoin.c    ft_strncmp.c\
	ft_strsplit.c   ft_isdigit.c    ft_memcmp.c     ft_putchar_fd.c\
	ft_putstr_fd.c  ft_strdel.c     ft_strlcat.c    ft_strncpy.c\
	ft_strstr.c     ft_atoi.c       ft_isprint.c    ft_memcpy.c\
	ft_putendl.c    ft_strcat.c     ft_strdup.c     ft_strlen.c\
	ft_strnequ.c    ft_strsub.c     ft_bzero.c      ft_itoa.c\
	ft_memdel.c     ft_putendl_fd.c ft_strchr.c     ft_strequ.c\
	ft_strmap.c     ft_strnew.c     ft_strtrim.c    ft_isalnum.c\
	ft_memalloc.c   ft_memmove.c    ft_putnbr.c     ft_strclr.c\
	ft_striter.c    ft_strmapi.c    ft_strnstr.c    ft_tolower.c\
	ft_lstnew.c		ft_lstadd.c		ft_lstdelone.c	ft_lstdel.c\
	ft_lstiter.c	ft_lstmap.c\
	\
	ft_sqrt_.c

OBJ		= $(SRC:.c=.o)

all : reset_cursor $(NAME)

$(NAME) : $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@printf "$(CUR_RST)$(CGREEN)BUILD LIBFT		: SUCCESS$(CRESET)$(CUR_CLR)\n"

%.o : %.c
	@gcc $(FLAGS) -I$(INCDIR) -c $< -o $@
	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)BUILD LIBFT		: $<$(CRESET)$(CUR_CLR)"

clean :
	@rm -f $(OBJ)
#	@printf "$(CYELLOW)LIBFT OBJECTS CLEARED01$(CRESET)\n"

fclean : clean
	@rm -f $(NAME)
	@printf "$(CYELLOW)RAZ LIBFT	: Ok$(CRESET)\n"


re : fclean all

####MORE_RULEZ####

reset_cursor :
	@printf "$(CUR_SVE)"
