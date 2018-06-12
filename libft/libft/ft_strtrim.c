/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:28:59 by galy              #+#    #+#             */
/*   Updated: 2016/11/21 19:35:24 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_cpy(char *dst, char const *src, int j, int len)
{
	int i;

	i = 0;
	while (j <= len)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

static int	cpt_blc(char const *src)
{
	int i;
	int cpt;

	cpt = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == ' ' || src[i] == '\n' || src[i] == '\t')
			cpt++;
		i++;
	}
	return (cpt);
}

static int	countdown(const char *s, int j, int len)
{
	while ((s[j] != '\0') && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j++;
	len--;
	if (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
	{
		while ((s[len] == ' ') || (s[len] == '\n') || (s[len] == '\t'))
			len--;
	}
	return (len);
}

char		*ft_strtrim(char const *s)
{
	char	*mod_s;
	int		len;
	int		j;
	int		cpt;

	cpt = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	len = (int)ft_strlen(s);
	cpt = cpt_blc(s);
	if (cpt == len)
	{
		if (NULL == (mod_s = ft_strcpy(ft_strnew(1), "")))
			return (NULL);
		return (mod_s);
	}
	while ((s[j] != '\0') && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j++;
	len = countdown(s, j, len);
	if (NULL == (mod_s = ft_strnew(len - j + 1)))
		return (NULL);
	ft_cpy(mod_s, s, j, len);
	return (mod_s);
}
