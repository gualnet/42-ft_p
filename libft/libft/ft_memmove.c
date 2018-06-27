/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:47:13 by galy              #+#    #+#             */
/*   Updated: 2017/12/08 21:48:06 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static	void	*ft_reverse_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char *dstuc;
	unsigned char *srcuc;

	dstuc = (unsigned char *)dst;
	srcuc = (unsigned char *)src;
	while (len)
	{
		len--;
		dstuc[len] = srcuc[len];
	}
	return (dst);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*srcuc;
	unsigned char	*dstuc;
	size_t			i;

	srcuc = (unsigned char	*)src;
	dstuc = (unsigned char	*)dst;
	if (len == 0 || dst == src)
		return (dst);
	i = len;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else if (dst > src)
		ft_reverse_memcpy(dst, src, len);
	return (dst);
}
