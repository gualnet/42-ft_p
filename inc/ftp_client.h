/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:06:19 by galy              #+#    #+#             */
/*   Updated: 2018/06/28 12:17:05 by galy             ###   ########.fr       */
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
	int					dtp_sock;
	unsigned int		cslen;
	//	-----	-----	-----
	char				*name;
	char				*passw;
	char				*cwd;
	//	-----	-----	-----
	// t_inet_info			n_info;
}						t_vault;









void	usage(char *str);
int		read_send_loop(char *name, int sock);
// int		init_cmd_connect(t_vault *vault, char **argv);




#endif