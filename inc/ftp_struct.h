/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:57:42 by galy              #+#    #+#             */
/*   Updated: 2018/06/19 12:29:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_STRUCT_H
# define FTP_STRUCT_H

typedef struct			s_inet_info
{
	struct sockaddr_in	cmd_sin;
	struct sockaddr_in	dtp_sin;
	// dtp_sock_addr
	// dtp_sock_port
}						t_inet_info;

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
	t_inet_info			n_info;
}						t_vault;


#endif