/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 18:34:29 by galy              #+#    #+#             */
/*   Updated: 2018/07/31 18:37:19 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		verif_dir_loop(char **lines, char *tmp)
{
	char	**inlines;
	int		match;
	int		i;
	int		j;

	match = 0;
	i = 1;
	j = 0;
	while (lines[i] != NULL)
	{
		if (ft_strstr(lines[i], tmp) != NULL && \
		ft_strstr(lines[i], tmp) != lines[i])
		{
			inlines = ft_strsplit(lines[i], ' ');
			while (inlines[j] != NULL)
			{
				if (inlines[j][0] == 'd' && inlines[8] != NULL && \
				ft_strcmp(inlines[8], tmp) == 0)
					match = 1;
				j++;
			}
		}
		i++;
	}
	return (match);
}

int		verif_dir(char **lines, char *str)
{
	char	*tmp;
	int		match;

	if (ft_strlen(str) <= 3)
		return (-1);
	if ((tmp = ft_strdup(str + 3)) == NULL)
		return (-1);
	truncate_end_signs(tmp);
	match = verif_dir_loop(lines, tmp);
	free(tmp);
	return (match);
}
