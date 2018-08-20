/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrsplited.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 12:06:47 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 14:25:19 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_freestrsplited(char **banana)
{
	int i;

	i = 0;
	while (banana[i] != NULL)
	{
		free(banana[i]);
		i++;
	}
	free(banana);
}
