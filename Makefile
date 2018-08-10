# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 0001/01/01 01:01:01 by galy              #+#    #+#              #
#    Updated: 2018/08/10 15:38:41 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY		: serveur client

NAME		=	ftp
CC			=	gcc

# CFLAGS		=	-Wall -Werror -Wextra
# CFLAGS		=	-Wall -Werror -Wextra -g
CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address
# CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address -g

LIBFLAG		=	-L./libft -lftall


####DIRECTORY####

INCDIR		=	inc
OBJDIR		=	obj
LIBDIR		=	libft
SRVDIR		=	src_server
CLTDIR		=	src_client

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
				cmd_cwd.c            cmd_pasv.c           cmd_type.c           init_connexion.c \
				cmd_cwd_2.c          cmd_port.c           cmd_user_pass.c      reader_sender.c \
				cmd_dele.c           cmd_pwd.c            create_child.c       server.c \
				cmd_list.c           cmd_retr.c           create_server.c      state_machine.c \
				cmd_list_2.c         cmd_retr_2.c         create_socket.c      truncate_end_signs.c \
				cmd_mkd.c            cmd_rmd.c            data_ex_ch.c         usage.c \
				cmd_mode.c           cmd_stor.c           dispatcher.c         verif_cmd_form.c \
				cmd_noop.c           cmd_syst.c           dtp_receiver.c

CLTSRC			=	\
				check_data_conection.c cmd_mkd.c              cmd_rmd.c \
				client.c               cmd_pasv.c             create_dtp_socket.c \
				cmd_cd.c               cmd_put_file.c         dtp_receiver.c \
				cmd_cd_2.c             cmd_put_file_2.c       init_vault.c \
				cmd_get_file.c         cmd_pwd.c              parsinterpreter.c \
				cmd_ls.c               cmd_quit.c             running_loop.c \
				cmd_ls_2.c             cmd_receiver.c         usage.c


####FUNC####

SRVOBJP		=	$(addprefix $(OBJDIR)/$(SRVDIR)/, $(SRVSRC:.c=.o))
CLTOBJP		=	$(addprefix $(OBJDIR)/$(CLTDIR)/, $(CLTSRC:.c=.o))


####RULEZ####

all			:	reset_screen serveur client

serveur		:  make_lib save_cursor $(SRVOBJP)
	@$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $(SRVOBJP) -o serveur
	@printf "$(CUR_RST)$(CGREEN)BUILD FT_P SERVER	: SUCCESS$(CRESET)$(CUR_CLR)\n"
	@printf "$(CUR_SVE)"

client		: make_lib save_cursor $(CLTOBJP)
	@$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $(CLTOBJP) -o client
	@printf "$(CUR_RST)$(CGREEN)BUILD FT_P CLIENT	: SUCCESS$(CRESET)$(CUR_CLR)\n"
	@printf "$(CUR_SVE)"

clean		:
	@make clean - C $(LIBDIR)
	@$(RM) -f $(OBJP)
	@$(RM) -rf $(OBJDIR)
#	@printf "$(CYELLOW)FTP	: CLEANED$(CRESET)\n"

mini_clean	:

	@$(RM) -f serveur
	@$(RM) -f client
	@$(RM) -f $(OBJP)
	@$(RM) -rf $(OBJDIR)

fclean		: mini_clean
	# @make fclean -C $(LIBDIR)
	@printf "$(CYELLOW)RAZ FT_P	: Ok$(CRESET)\n"
	@printf "\n"

re			: fclean all

# - Clear the screen, move to (0,0):
#   \033[2J
# - Erase to end of line:
#   \033[K

# - Save cursor position:
#   \033[s
# - Restore cursor position:
#   \033[u

####MORE_RULEZ####

$(OBJDIR)/$(SRVDIR)/%.o	:	$(SRVDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(SRVDIR)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
	@printf "$(CUR_RST)$(CYELLOW)BUILD FT_P SERVER	: $<$(CRESET)$(CUR_CLR)\n"

$(OBJDIR)/$(CLTDIR)/%.o	:	$(CLTDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(CLTDIR)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
	@printf "$(CUR_RST)$(CYELLOW)BUILD FT_P CLIENT	: $<$(CRESET)$(CUR_CLR)\n"


make_lib	:
	@make -C $(LIBDIR)

save_cursor :
	@printf "$(CUR_SVE)"

reset_screen :
	@printf "\033[2J"
	@printf "\033[500A"
	

# OBJD		:
#	@mkdir -p $(OBJDIR)
#	@mkdir -p $(OBJDIR)/$(SRVDIR)
#	@mkdir -p $(OBJDIR)/$(CLTDIR)