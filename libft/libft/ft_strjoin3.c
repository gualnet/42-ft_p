/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:36:16 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 14:26:40 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	cpy_to_dst(char *dst, char const *s1, char const *s2, \
char const *s3)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s1[i] != '\0')
	{
		dst[len] = s1[i];
		i++;
		len++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		dst[len] = s2[i];
		i++;
		len++;
	}
	i = 0;
	while (s3[i] != '\0')
	{
		dst[len] = s3[i];
		i++;
		len++;
	}
}

char		*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*dst;
	size_t	len;

	if (s1 == NULL)
		s1 = "";
	else if (s2 == NULL)
		s2 = "";
	else if (s3 == NULL)
		s3 = "";
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(dst = (char *)malloc(sizeof(*dst) * (len + 1))))
		return (NULL);
	ft_bzero(dst, len + 1);
	cpy_to_dst(dst, s1, s2, s3);
	return (dst);
}
