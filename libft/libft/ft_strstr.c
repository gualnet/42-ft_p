/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:38:49 by galy              #+#    #+#             */
/*   Updated: 2016/11/21 10:29:26 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[k] != '\0')
	{
		j = 0;
		i = k;
		while (little[j] == big[i])
		{
			ret = ((char *)big);
			i++;
			j++;
			if (little[j] == '\0')
				return (&(ret[i - (ft_strlen(little))]));
		}
		k++;
	}
	return (NULL);
}
