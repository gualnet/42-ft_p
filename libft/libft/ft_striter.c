/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:29:29 by galy              #+#    #+#             */
/*   Updated: 2016/11/21 20:50:21 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_striter(char *s, void (*f)(char *))
{
	int i;

	i = 0;
	if (s != NULL && *f != NULL)
	{
		while (s[i] != '\0')
		{
			f(s + i);
			i++;
		}
	}
}