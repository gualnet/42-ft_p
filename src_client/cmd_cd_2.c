/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 18:34:29 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 16:52:13 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	free_2d_char_tab(char **tab)
{
	int		i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		verif_dir_loop(char **lines, char *tmp, int match)
{
	char	**inlines;
	int		i;
	int		j;

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
	free_2d_char_tab(inlines);
	return (match);
}

int		verif_dir(char **lines, char *str)
{
	char	*tmp;
	int		match;

	match = 0;
	if (ft_strlen(str) <= 3)
		return (-1);
	if ((tmp = ft_strdup(str + 3)) == NULL)
		return (-1);
	truncate_end_signs(tmp);
	match = verif_dir_loop(lines, tmp, match);
	free(tmp);
	return (match);
}
