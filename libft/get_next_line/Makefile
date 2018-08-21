# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 16:28:28 by galy              #+#    #+#              #
#    Updated: 2018/03/09 20:31:38 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	get_next_line.a
FLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	.
OBJDIR	=	.
INCDIR	=	.\
			../libft

LIBFT	=	-L../libft -lft

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

SRC		=	\
			get_next_line.c

OBJ		= $(SRC:.c=.o)
INCP	=	$(foreach dir, $(INCDIR), -I$(dir))

all : reset_cursor $(NAME)

$(NAME) : make_libft $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@printf "$(CUR_RST)$(CGREEN)BUILD GNL		: SUCCESS$(CRESET)$(CUR_CLR)\n"


%.o : %.c
	@gcc $(FLAGS) $(INCP) -c $< -o $@
	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)BUILD GNL		: $<$(CRESET)$(CUR_CLR)"

clean :
	@rm -f $(OBJ)
#	@printf "$(CYELLOW)GNL OBJECT CLEARED$(CRESET)\n"

fclean : clean
#	@make fclean -C ../libft
	@rm -f $(NAME)
	@printf "$(CYELLOW)RAZ GNL		: Ok$(CRESET)\n"

re : fclean all

####MORE_RULEZ####

make_libft :
	@make -C ../libft

reset_cursor :
	@printf "$(CUR_SVE)"
