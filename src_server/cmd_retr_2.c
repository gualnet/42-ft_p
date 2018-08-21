/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 17:39:15 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 17:39:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		prep_transfer_retr(t_vault *vault, char *file, t_file_info *fi)
{
	char	*tmp;

	tmp = ft_strjoin(vault->cwd, "/");
	fi->path = ft_strjoin(tmp, file);
	free(tmp);
	truncate_end_signs(fi->path);
	if ((fi->fd = open(fi->path, O_RDONLY | O_NONBLOCK)) < 0)
	{
		ft_printf("[ERROR] Unable to open \'%s\'", fi->path);
		return (-1);
	}
	if (fstat(fi->fd, &fi->fstat) == -1)
		return (-2);
	if ((fi->fdump = (void*)mmap(NULL, fi->fstat.st_size, PROT_READ, \
	MAP_FILE | MAP_PRIVATE, fi->fd, 0)) == MAP_FAILED)
		return (-3);
	return (1);
}
