/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:35:20 by galy              #+#    #+#             */
/*   Updated: 2017/06/03 16:16:42 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*mask_filler(int masklvl, char *bin)
{
	char	*tab_mask[4];
	char	*mask;
	int		i;
	int		j;

	tab_mask[0] = "110.....10......";
	tab_mask[1] = "1110....10......10......";
	tab_mask[2] = "11110...10......10......10......";
	tab_mask[3] = NULL;
	if ((mask = ft_strdup(tab_mask[masklvl])) == NULL)
		exit(-1);
	i = 0;
	j = ft_strlen(mask);
	while (bin[i] != '\0' || j > 0)
	{
		if (mask[j] == '.' && bin[i] != '\0')
		{
			mask[j] = bin[i];
			i++;
		}
		else if (mask[j] == '.' && bin[i] == '\0')
			mask[j] = '0';
		j--;
	}
	return (mask);
}

static void	ft_itob(wchar_t lettre, char *bin)
{
	int		result;
	int		i;
	char	*tmppipe;

	i = 0;
	while (i < 32 && lettre != 0)
	{
		result = 0;
		result = lettre % 2;
		lettre -= (lettre / 2) + result;
		tmppipe = ft_itoa(result);
		bin[i] = *tmppipe;
		i++;
		free(tmppipe);
	}
}

/*
**	prend le binaire d'une wchar et compose le tableau lettre[]
**	avec la traduction de chacun des octets qui compose le wchar
*/

static void	conv_bto_wchartab_2(char *binstr, unsigned char *lettre, int j)
{
	char	c[2];
	int		i;
	int		res;
	int		cpt;

	ft_bzero(c, 2);
	i = 0;
	res = 0;
	cpt = 7;
	while (binstr[i] != '\0')
	{
		c[0] = binstr[i];
		res = ft_atoi(c) * ft_power(2, cpt) + res;
		if (cpt == 0)
		{
			lettre[j] = res;
			j++;
			res = 0;
			cpt = 8;
		}
		i++;
		cpt--;
	}
}

/*
**	write tour a tour de chacun des octets du wchar
**	transmis par le tableau lettre
*/

static int	ft_conv_bto_wchartab(char *binstr)
{
	unsigned char	lettre[4];
	int				j;

	j = 0;
	conv_bto_wchartab_2(binstr, lettre, j);
	while (lettre[j] != 0 && j < MB_CUR_MAX)
	{
		write(1, &lettre[j], 1);
		j++;
	}
	if (192 <= lettre[0] && lettre[0] < 224 && j != 2 && MB_CUR_MAX != 1)
		return (-1);
	if (224 <= lettre[0] && lettre[0] < 240 && j != 3)
		return (-1);
	free(binstr);
	return (j);
}

int			ft_putwchar(wchar_t lettre)
{
	char	bin[32];
	int		binlen;
	char	*binstr;

	if (lettre <= 127)
		ft_putchar(lettre);
	else
	{
		binstr = NULL;
		ft_bzero(bin, 32);
		ft_itob(lettre, bin);
		binlen = ft_strlen(bin);
		if (binlen >= 8 && binlen <= 11)
			return (ft_conv_bto_wchartab(binstr = mask_filler(0, bin)));
		else if (binlen >= 12 && binlen <= 16)
			return (ft_conv_bto_wchartab(binstr = mask_filler(1, bin)));
		else if (binlen >= 17 && binlen <= 23)
			return (ft_conv_bto_wchartab(binstr = mask_filler(2, bin)));
		free(binstr);
	}
	return (1);
}
