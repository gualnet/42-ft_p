/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:33:20 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 21:00:01 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*create_width_str(char *str, t_flags *flag)
{
	char	*wdtstr;
	int		wdtlen;
	int		i;

	wdtlen = flag->width - ft_strlen(str);
	if (wdtlen <= 0)
	{
		if ((wdtstr = ft_strdup("")) == NULL)
			exit(-1);
		return (wdtstr);
	}
	if ((wdtstr = ft_strnew(wdtlen + 1)) == NULL)
		exit(-1);
	i = 0;
	while (i < wdtlen)
	{
		if (flag->zero == 1)
			wdtstr[i] = '0';
		else
			wdtstr[i] = ' ';
		i++;
	}
	return (wdtstr);
}

char		*flag_width_s_exec(char *str, t_flags *flag)
{
	char	*wdtstr;
	char	*newstr;

	if (flag->width < (int)ft_strlen(str))
		return (str);
	wdtstr = create_width_str(str, flag);
	if (flag->minus == 0)
		newstr = ft_strjoin(wdtstr, str);
	else
		newstr = ft_strjoin(str, wdtstr);
	if (newstr == NULL)
		exit(-1);
	free(wdtstr);
	free(str);
	return (newstr);
}
