/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 15:03:02 by galy              #+#    #+#             */
/*   Updated: 2018/08/01 15:03:20 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	print_dir_content_2(t_vault *vault, char **line)
{
	int		i;
	int		cpt;

	i = 1;
	cpt = 0;
	ft_printf("\n\n\033[37;1;4mFile:\033[0m\n");
	while (vault->s_dir_content[i] != NULL)
	{
		line = ft_strsplit(vault->s_dir_content[i], ' ');
		if (line[0][0] != 'd' && line[8] != NULL)
		{
			if (line[0][9] == 'x' && line[8] != NULL)
				ft_printf("\033[31m %s\t\033[0m", line[8]);
			else
				ft_printf("%s\t", line[8]);
		}
		ft_freestrsplited(line);
		if (cpt != 0 && ((cpt % 4) == 0))
		{
			ft_printf("\n", cpt);
			cpt = 0;
		}
		i++;
	}
}

void	print_dir_content(t_vault *vault)
{
	int		i;
	char	**line;
	int		cpt;

	i = 1;
	cpt = 0;
	ft_printf("\n\033[36;1;4mDir:\033[0m\n");
	while (vault->s_dir_content[i] != NULL)
	{
		line = ft_strsplit(vault->s_dir_content[i], ' ');
		if (line[0][0] == 'd' && line[8] != NULL)
		{
			ft_printf("\033[36m%s\t\033[0m", line[8]);
			cpt++;
		}
		ft_freestrsplited(line);
		if (cpt != 0 && ((cpt % 4) == 0))
		{
			ft_printf("\n", cpt);
			cpt = 0;
		}
		i++;
	}
	print_dir_content_2(vault, line);
	ft_printf("\n\n");
}
