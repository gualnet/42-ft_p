# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 0001/01/01 01:01:01 by galy              #+#    #+#              #
#    Updated: 2018/07/23 11:09:21 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY		: serveur, client

NAME		=	ftp
CC			=	gcc

# CFLAGS		=	-Wall -Werror -Wextra
# CFLAGS		=	-Wall -Werror -Wextra -g
# CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address
CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address -g

LIBFLAG		=	-L./libft -lftall


####DIRECTORY####

INCDIR		=	inc
OBJDIR		=	obj
LIBDIR		=	libft
SRVDIR		=	server
CLTDIR		=	client

####COLOR-SET####

CRESET		=	\033[0m
CRED		=	\033[31m
CGREEN		=	\033[32m
CYELLOW		=	\033[33m
CBLUE		=	\033[34m
CMAGENTA	=	\033[35m
CCYAN		=	\033[36m
CWHITE		=	\033[37m

####CURSOR-SET####
CUR_SVE		=	\033[s
CUR_RST		=	\033[u
CUR_CLR		=	\033[K

####FILES####

SRVSRC			=	\
				create_child.c		create_server.c		server.c		usage.c \
				init_connexion.c	state_machine.c		reader_sender.c verif_cmd_form.c \
				dispatcher.c		data_ex_ch.c		\
				cmd_user_pass.c		cmd_type.c			cmd_syst.c		cmd_pwd.c \
				cmd_pasv.c			cmd_list.c			cmd_cwd.c		cmd_stor.c \
				cmd_retr.c			cmd_mkd.c			cmd_noop.c		cmd_mode.c \
				cmd_port.c			cmd_dele.c			cmd_rmd.c		truncate_end_signs.c

CLTSRC			=	\
				client.c			usage.c				running_loop.c	\
				init_cmd_connect.c	parsinterpreter.c	sender_receiver.c\
				cmd_pwd.c			cmd_cd.c			cmd_ls.c		cmd_quit.c\
				cmd_pasv.c			cmd_get_file.c		cmd_put_file.c	dtp_receiver.c\
				create_dtp_socket.c	check_data_conection.c


####FUNC####

SRVOBJP		=	$(addprefix $(OBJDIR)/$(SRVDIR)/, $(SRVSRC:.c=.o))
CLTOBJP		=	$(addprefix $(OBJDIR)/$(CLTDIR)/, $(CLTSRC:.c=.o))


####RULEZ####

all			:	reset_cursor make_lib OBJD serveur client

common		: 

serveur		: $(SRVOBJP)
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $^ -o ftp_server

client		: $(CLTOBJP)
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $^ -o ftp_client
#	@printf "$(CUR_RST)$(CGREEN)BUILD MALLOC		: SUCCESS$(CRESET)$(CUR_CLR)\n"

clean		:
	@make clean - C $(LIBDIR)
	@$(RM) -f $(OBJP)
	@$(RM) -rf $(OBJDIR)
#	@printf "$(CYELLOW)MALLOC	: CLEANED$(CRESET)\n"

mini_clean	:

	@$(RM) -f $(NAME)_server
	@$(RM) -f $(NAME)_client
	@$(RM) -f $(OBJP)
	@$(RM) -rf $(OBJDIR)

fclean		: mini_clean
	# @make fclean -C $(LIBDIR)
	@printf "$(CYELLOW)RAZ MALLOC	: Ok$(CRESET)\n"
	@printf "\n"

re			: fclean all


####MORE_RULEZ####

$(OBJDIR)/$(SRVDIR)/%.o	:	$(SRVDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/$(CLTDIR)/%.o	:	$(CLTDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# $(OBJDIR)/$(CLTDIR)/%.o	:	$(CLTDIR)/%.c
# 	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
#	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)BUILD MALLOC		: $<$(CRESET)$(CUR_CLR)"

make_lib	:
	@make -C $(LIBDIR)

reset_cursor :
	@printf "$(CUR_SVE)"

OBJD		:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(SRVDIR)
	@mkdir -p $(OBJDIR)/$(CLTDIR)