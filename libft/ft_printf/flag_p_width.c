/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_p_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 19:35:07 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 12:11:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_width_p_exec(char *str, t_flags *flag)
{
	int		nbspace;
	int		i;
	char	*strspace;
	char	*newstr;

	if ((int)ft_strlen(str) > flag->width)
		return (str);
	nbspace = flag->width - (int)ft_strlen(str);
	if ((strspace = ft_strnew(nbspace + 1)) == NULL)
		exit(-1);
	i = -1;
	while (i < nbspace)
	{
		if (flag->zero == 1 && flag->minus == 0)
			strspace[i++] = '0';
		else
			strspace[i++] = ' ';
	}
	if (flag->minus == 0 && flag->zero == 0)
		newstr = ft_strjoin(strspace, str);
	else
		newstr = ft_strjoin(str, strspace);
	free(strspace);
	free(str);
	return (newstr);
}
