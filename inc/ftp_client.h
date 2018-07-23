/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:06:19 by galy              #+#    #+#             */
/*   Updated: 2018/07/23 11:20:20 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_CLIENT_H
# define FTP_CLIENT_H


#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

// #include "ftp_struct.h"
#include "libft.h"
#include "ft_printf.h"

#define BUF_SIZE	1024
// #define BUF_SIZE	10
#define CMD_PRINT	1
#define CMD_NOPRINT	0

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
	char				*s_cwd;
	char				*s_dir_content_name;
	char				**s_dir_content;
	char				*c_cwd;
	char				*c_dir_content_name;
	char				**c_dir_content;
	//	-----	-----	-----
	// t_inet_info			n_info;
}						t_vault;

typedef struct			s_file_info
{
	char				*path;
	int					fd;
	void				*fdump;
	struct stat 		fstat;
	unsigned long		dump_len;
}						t_file_info;

void	usage(char *str);
void	running_loop(t_vault *vault, char *name);
int		parsinterpreter(t_vault *vault, char *str);
char	*cmd_receiver(int sock);
char	*pasv(t_vault *vault);
int		create_dtp_sock(t_vault *vault, char *params);
void	truncate_end_signs(char *str);
int		check_data_conection(t_vault *vault);
char	*dtp_receiver(int sock, ssize_t	*size);

int		cmd_pwd(t_vault *vault, char *str, int print);
int		cmd_cd(t_vault *vault, char *str);
int		cmd_ls(t_vault *vault, char *str, int	print);
int		cmd_get_file(t_vault *vault, char *str);
int		cmd_put_file(t_vault *vault, char *str);
int		cmd_quit(t_vault *vault, char *str);

#endif
