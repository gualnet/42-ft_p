/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:47:37 by galy              #+#    #+#             */
/*   Updated: 2018/06/13 19:17:40 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_SERVER_H
# define FTP_SERVER_H


#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "ftp_struct.h"
#include "libft.h"
#include "ft_printf.h"



void	usage(char *str);
int		create_server(int port);
int		create_child_process(t_vault *vault);
int		init_connexion(t_vault *vault);
int		state_machine(t_vault *vault, uint state);
int		store_user(t_vault *vault, char *cmd);


#endif