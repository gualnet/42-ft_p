/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:08:55 by galy              #+#    #+#             */
/*   Updated: 2017/06/02 22:18:12 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	char			*big_bis;

	i = 0;
	big_bis = ft_strnew(len);
	big_bis = ft_strncpy(big_bis, big, len);
	if (little[0] == '\0')
		return ((char *)big);
	else if (len == 0)
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0] && (ft_memcmp((&(big_bis[i])),\
		little, ft_strlen(little)) == 0))
		{
			free(big_bis);
			return ((char *)(&(big[i])));
		}
		i++;
	}
	free(big_bis);
	return (NULL);
}
