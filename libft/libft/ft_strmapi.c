/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:49:02 by galy              #+#    #+#             */
/*   Updated: 2016/11/22 15:46:52 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	char			*mod_s;
	unsigned int	i;

	mod_s = (char *)s;
	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	if (!(new_str = (char *)malloc(sizeof(*new_str) * (ft_strlen(s) + 1))))
		return (NULL);
	while (mod_s[i] != '\0')
	{
		new_str[i] = f(i, mod_s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
