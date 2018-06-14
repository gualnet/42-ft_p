/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:57:42 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 18:43:58 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_STRUCT_H
# define FTP_STRUCT_H


typedef struct	s_vault
{
	int				cs;
	unsigned int	cslen;

	// ------------
	char			*name;
	char			*passw;
	char			*cwd;
}				t_vault;


#endif