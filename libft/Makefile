# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 16:28:28 by galy              #+#    #+#              #
#    Updated: 2018/03/09 20:50:31 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftall.a
CFLAGS	=	-Wall -Werror -Wextra

DIRLIBFT	=	./libft
DIRGNL		=	./get_next_line
DIRFTPRINTF	=	./ft_printf

SRCLIBFT	=\
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
	ft_lstiter.c	ft_lstmap.c		ft_sqrt_.c

SRCGNL		=\
	get_next_line.c\

SRCFTPRINTF	=\
	flag_b.c            flag_filler_02.c    flag_o.c            flag_s_precision.c\
	flag_c.c            flag_filler_cs.c    flag_p.c            flag_s_width.c\
	flag_d.c            flag_filler_diu.c   flag_p_precision.c  flag_sharp.c\
	flag_d_precision.c  flag_filler_lhjz.c  flag_p_width.c      flag_u.c\
	flag_d_space.c      flag_filler_oxp.c   flag_percent.c      flag_x.c\
	flag_d_width.c      flag_ls_precision.c flag_plus.c         flag_x_precision.c\
	flag_filler_01.c    flag_ls_width.c     flag_s.c            flag_x_width.c\
	ft_atoll.c          ft_power.c          ft_putwchar.c       ft_wcharlen.c\
	ft_imaxtoabase.c    ft_printf.c         ft_putwstr.c        ft_wstrdup.c\
	ft_imaxtoabase_02.c ft_printf.h         ft_wstrlen.c        ft_ubase_converter.c\
	ft_lltoa.c          ft_putbuffer.c      ft_ulltoa.c         tabfct.c\

####COLOR-SET####

CRESET		=	\033[0m
CRED		=	\033[31m
CGREEN		=	\033[32m
CGREEN+		=	\033[32;1;5m
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

OBJLIBFT	=	$(addprefix $(DIRLIBFT)/, $(SRCLIBFT:.c=.o))
OBJGNL	=	$(addprefix $(DIRGNL)/, $(SRCGNL:.c=.o))
OBJFTPRINTF	=	$(addprefix $(DIRFTPRINTF)/, $(SRCFTPRINTF:.c=.o))

all : reset_cursor $(NAME)

$(NAME)	: make_libs
	@ar -rc $(NAME) $(OBJLIBFT)
#	@printf "$(CUR_SVE)$(CYELLOW)Adding libft.a to $(NAME)$(CRESET)$(CUR_CLR)"
	@ar -rc $(NAME) $(OBJGNL)
#	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)Adding get_next_line.a to $(NAME)$(CRESET)$(CUR_CLR)"
	@ar -rc $(NAME) $(OBJFTPRINTF)
#	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)Adding ft_printf.a to $(NAME)$(CRESET)$(CUR_CLR)"
	@printf "$(CUR_RST)$(CGREEN)MERGE FULL LIBFT 	: SUCCESS$(CRESET)\n"

clean :
	@make clean -C ./libft
	@make clean -C ./get_next_line
	@make clean -C ./ft_printf
	@printf "$(CYELLOW)LIBFT	: CLEANED $(CRESET)\n"

fclean :
	@printf "$(CMAGENTA) call fclean libftall $(CRESET)\n"
	@make fclean -C ./libft
	@make fclean -C ./get_next_line
	@make fclean -C ./ft_printf
	@rm -f $(NAME)
	
re : fclean all

####MORE_RULEZ####

make_libs :
	@make -C ./libft
	@make -C ./get_next_line
	@make -C ./ft_printf

reset_cursor :
	@printf "$(CUR_SVE)"
