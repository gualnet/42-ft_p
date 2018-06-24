/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:47:37 by galy              #+#    #+#             */
/*   Updated: 2018/06/22 17:26:41 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_SERVER_H
# define FTP_SERVER_H

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <sys/mman.h>


#include "ftp_struct.h"
#include "libft.h"
#include "ft_printf.h"


/*
**	Defines
*/

#define R_BUFF_SIZE			1024	// read buffer size
#define CMD_SP_LEN			5		// cmd + space len before argument
// #define	GETCWD_BUF_SIZE		128
#define	GETCWD_BUF_SIZE		128
#define CMD_SOCK_QUEUE		10
#define DTP_SOCK_QUEUE		1
#define CMD_SOCK			1
#define DTP_SOCK			2


/*
**	Func
*/

void	usage(char *str);
int		create_server(t_vault *vault, int port);
int		create_child_process(t_vault *vault);
int		init_connexion(t_vault *vault);
int		state_machine(t_vault *vault, uint state);
int		read_sock(t_vault *vault, char *buff);
int		sender_sock(t_vault *vault, char *msg);
int		create_dtp_socket(t_vault *vault);
int		sender_dtp_bin(t_vault *vault, void *msg, size_t len);
int		sender_dtp(t_vault *vault, char *msg);
int		dispatcher(t_vault *vault, char *buff);
int		wait_for_conn(t_vault *vault);

//????
void	list_dtp_response(t_vault *vault);

int		cmd_user(t_vault *vault, char *cmd);
int		cmd_pass(t_vault *vault, char *cmd);
int		cmd_cwd(t_vault *vault, char *cmd);
int		cmd_retr(t_vault *vault, char *cmd);
int		cmd_pwd(t_vault *vault);
int		cmd_syst(t_vault *vault);
int		cmd_type(t_vault *vault);
int		cmd_pasv(t_vault *vault);
int		cmd_list(t_vault *vault);

#endif