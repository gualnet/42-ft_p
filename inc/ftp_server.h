/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:47:37 by galy              #+#    #+#             */
/*   Updated: 2018/06/13 12:19:45 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_SERVER_H
# define FTP_SERVER_H


#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "libft.h"
#include "ft_printf.h"



void	usage(char *str);


#endif