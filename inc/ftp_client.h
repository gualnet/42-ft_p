/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:06:19 by galy              #+#    #+#             */
/*   Updated: 2018/07/04 12:48:17 by galy             ###   ########.fr       */
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
	char				**dir_content_name;
	char				**dir_content_type;
	//	-----	-----	-----
	// t_inet_info			n_info;
}						t_vault;









void	usage(char *str);
int		read_send_loop(char *name, int sock);
void	parsinterpreter(int sock, char *buf);
char	*cmd_receiver(int sock);

int		cmd_pwd(int sock, char *str);
int		cmd_cd(int sock, char *str);
int		cmd_list(int sock, char *str);



#endif