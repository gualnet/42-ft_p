/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:20:28 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 20:01:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*check_flag_smod(char *str, t_flags *flag)
{
	if (flag->precision_on == 0)
	{
		flag->precision_on = 1;
		flag->precision = (int)ft_strlen(str);
	}
	if (flag->precision < (int)ft_strlen(str))
		str = flag_precision_s_exec(str, flag);
	else
	{
		if ((str = ft_strdup(str)) == NULL)
			exit(-1);
	}
	if (flag->width != 0)
		str = flag_width_s_exec(str, flag);
	return (str);
}

static wchar_t	*check_flag_lsmod(wchar_t *wstr, t_flags *flag)
{
	if (flag->precision_on == 0)
	{
		flag->precision_on = 1;
		flag->precision = ft_wstrlen(wstr);
	}
	if (flag->precision < ft_wstrlen(wstr))
		wstr = flag_precision_ls_exec(wstr, flag);
	else
	{
		if ((wstr = ft_wstrdup(wstr)) == NULL)
			exit(-1);
	}
	if (flag->width != 0)
		wstr = flag_width_ls_exec(wstr, flag);
	return (wstr);
}

static int		null_str(void)
{
	char *nullmsg;

	nullmsg = "(null)";
	ft_putbuffer(nullmsg);
	return (ft_strlen(nullmsg));
}

static int		flag_ls(va_list ap, t_flags *flag)
{
	wchar_t	*wstr;
	int		lenstr;
	int		freeit;

	freeit = 0;
	if ((wstr = va_arg(ap, wchar_t*)) == NULL)
		return (null_str());
	if (flag->precision < ft_wstrlen(wstr))
		freeit = 1;
	wstr = check_flag_lsmod(wstr, flag);
	lenstr = ft_putwstr(wstr);
	free(wstr);
	return (lenstr);
}

int				flag_s(va_list ap, t_flags *flag)
{
	char	*str;
	int		lenstr;
	int		freeit;

	freeit = 0;
	if (flag->fl_l == 0)
	{
		if ((str = va_arg(ap, char*)) == NULL)
			return (null_str());
		if (flag->precision < (int)ft_strlen(str))
			freeit = 1;
		str = check_flag_smod(str, flag);
		ft_putbuffer(str);
		lenstr = (int)ft_strlen(str);
		free(str);
	}
	else
		lenstr = flag_ls(ap, flag);
	return (lenstr);
}
