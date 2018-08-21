/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:51:11 by galy              #+#    #+#             */
/*   Updated: 2016/11/07 18:42:15 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*fresh;
	char	*z;

	fresh = malloc(size);
	if (fresh == NULL)
		return (NULL);
	i = 0;
	z = fresh;
	while (i < size)
	{
		z[i] = '\0';
		i++;
	}
	return (fresh);
}
