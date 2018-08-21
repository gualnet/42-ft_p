/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:49:53 by galy              #+#    #+#             */
/*   Updated: 2016/11/22 18:20:42 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		(((unsigned char *)dst)[i]) = (((unsigned char *)src)[i]);
		if ((((unsigned char *)src)[i]) == ((unsigned char)c))
			return (&((unsigned char *)dst)[i + 1]);
		i++;
	}
	return (NULL);
}
