/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 20:00:03 by galy              #+#    #+#             */
/*   Updated: 2016/11/23 13:01:40 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	initlen;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	initlen = i;
	if (size == 0)
		return (ft_strlen(src));
	while ((src[j] != '\0') && (i < size - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (size < initlen)
		return (ft_strlen(src) + size);
	return (initlen + ft_strlen(src));
}
