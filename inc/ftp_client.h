/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:06:19 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 16:49:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_CLIENT_H
# define FTP_CLIENT_H

# include <netinet/in.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# include "libft.h"
# include "ft_printf.h"

/*
**	Defines
*/

# define BUF_SIZE		1024
# define CMD_PRINT		1
# define CMD_NOPRINT	0

/*
**	Struct
*/

typedef struct		s_vault
{
	int				csc;
	int				csd;
	char			*name;
	char			*passw;
	char			*s_cwd;
	char			*s_dir_content_name;
	char			**s_dir_content;
	char			*c_cwd;
	char			*c_dir_content_name;
	char			**c_dir_content;
}					t_vault;

typedef struct		s_file_info
{
	char			*path;
	int				fd;
	void			*fdump;
	struct stat		fstat;
	unsigned long	dump_len;
}					t_file_info;

typedef struct		s_strings
{
	char			buf[BUF_SIZE + 1];
	char			*cmd;
	char			*tmp;
	ssize_t			size;
	int				breaker;
}					t_strings;

/*
**	Func
*/

void				usage(char *str);
void				running_loop(t_vault *vault, char *name);
int					parsinterpreter(t_vault *vault, char *str);
char				*cmd_receiver(int sock);
char				*pasv(t_vault *vault);
int					create_dtp_sock(t_vault *vault, char *params);
void				truncate_end_signs(char *str);
int					check_data_conection(t_vault *vault);
char				*dtp_receiver(int sock, ssize_t	*size);
void				init_vault(t_vault *vault);
void				free_vault(t_vault *vault);
char				*loop_getcwd(void);
void				free_2d_char_tab(char **tab);

int					cmd_pwd(t_vault *vault, char *str, int print);
int					cmd_cd(t_vault *vault, char *str);
int					verif_dir(char **lines, char *str);

int					cmd_ls(t_vault *vault, char *str, int	print);
void				print_dir_content(t_vault *vault);

int					cmd_get_file(t_vault *vault, char *str);
int					cmd_put_file(t_vault *vault, char *str);
int					cmd_mkd(t_vault *vault, char *str);
int					cmd_rmd(t_vault *vault, char *str);
int					cmd_quit(t_vault *vault, char *str);

int					srv_com_exchange_put(t_vault *vault, \
char *cmd, t_file_info *file);

#endif
