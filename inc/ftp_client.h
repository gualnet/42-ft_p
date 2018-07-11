/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:06:19 by galy              #+#    #+#             */
/*   Updated: 2018/07/10 23:46:08 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_CLIENT_H
# define FTP_CLIENT_H


#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// #include "ftp_struct.h"
#include "libft.h"
#include "ft_printf.h"

// #define BUF_SIZE	1024
#define BUF_SIZE	10

typedef struct			s_vault
{
	int					csc;
	int					csd;

	int					cmd_sock;
	int					dtp_sock;
	// unsigned int		cslen;
	//	-----	-----	-----
	char				*name;
	char				*passw;
	char				*cwd;
	char				*dir_content_name;
	char				**dir_content;
	//	-----	-----	-----
	// t_inet_info			n_info;
}						t_vault;


void	usage(char *str);
int		read_send_loop(t_vault *vault, char *name);
void	parsinterpreter(t_vault *vault, char *str);
char	*cmd_receiver(int sock);
char	*pasv(t_vault *vault);
int		create_dtp_sock(t_vault *vault, char *params);
void	truncate_end_signs(char *str);

int		cmd_pwd(t_vault *vault, char *str);
int		cmd_cd(t_vault *vault, char *str);
int		cmd_list(t_vault *vault, char *str);


#endif
