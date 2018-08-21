# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 16:28:28 by galy              #+#    #+#              #
#    Updated: 2018/03/09 20:41:05 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ftprintf.a
CFLAGS	=	-Wall -Werror -Wextra

SRCDIR	=	.
OBJDIR	=	.
INCDIR	=	.\
			../libft

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
			ft_printf.c   tabfct.c\
			flag_d.c   flag_plus.c   flag_d_space.c   flag_d_width.c   flag_d_precision.c\
			flag_u.c\
			flag_o.c   flag_sharp.c\
			flag_x.c   flag_x_precision.c   flag_x_width.c\
			flag_c.c   ft_putwchar.c   ft_power.c\
			flag_s.c   flag_s_precision.c   flag_s_width.c   flag_ls_precision.c   flag_ls_width.c\
			flag_p.c   flag_p_precision.c   flag_p_width.c\
			flag_percent.c\
			flag_b.c\
			flag_filler_01.c   flag_filler_02.c   flag_filler_lhjz.c   flag_filler_diu.c   flag_filler_oxp.c   flag_filler_cs.c\
			ft_lltoa.c   ft_imaxtoabase.c	ft_atoll.c   ft_ulltoa.c   ft_ubase_converter.c\
			ft_wstrlen.c   ft_imaxtoabase_02.c   ft_wcharlen.c   ft_putwstr.c   ft_wstrdup.c\
			ft_putbuffer.c

OBJ		= $(SRC:.c=.o)
INCP	=	$(foreach dir, $(INCDIR), -I$(dir))

all : reset_cursor $(NAME)

$(NAME) : make_libft $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@printf "$(CUR_RST)$(CGREEN)BUILD FT_PRINTF		: SUCCESS$(CRESET)$(CUR_CLR)\n"

%.o : %.c
	@gcc $(FLAGS) $(INCP) -c $< -o $@
	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)BUILD FT_PRINTF		: $<$(CRESET)$(CUR_CLR)"


clean :
	@rm -f $(OBJ)
#	@printf "$(CYELLOW)FT_PRINTF OBJECTS CLEARED$(CRESET)\n"

fclean : clean
#	@make fclean -C ../libft
	@rm -f $(NAME)
	@printf "$(CYELLOW)RAZ FT_PRINTF	: Ok$(CRESET)\n"

re : fclean all

####MORE_RULEZ####

make_libft :
	@make -C ../libft

reset_cursor :
	@printf "$(CUR_SVE)"
