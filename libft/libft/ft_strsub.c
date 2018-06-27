/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:42:37 by galy              #+#    #+#             */
/*   Updated: 2016/11/21 17:48:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str_dest;

	if (s == NULL)
		return (NULL);
	if (!(str_dest = (char*)malloc(sizeof(*str_dest) * (len + 1))))
		return (NULL);
	ft_strncpy(str_dest, s + start, len);
	str_dest[len] = '\0';
	return (str_dest);
}
