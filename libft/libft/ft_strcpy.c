/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:25:40 by galy              #+#    #+#             */
/*   Updated: 2016/11/07 18:31:36 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int src_len;
	int i;

	i = 0;
	src_len = ft_strlen(src);
	while (i != src_len + 1)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
