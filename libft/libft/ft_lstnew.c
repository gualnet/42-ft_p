/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 17:26:44 by galy              #+#    #+#             */
/*   Updated: 2017/03/16 02:18:51 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh_elem;

	if (NULL == (fresh_elem = (t_list *)malloc(sizeof(*fresh_elem))))
		return (NULL);
	fresh_elem->content_size = (!content) ? 0 : content_size;
	if (content == NULL)
		fresh_elem->content = NULL;
	else
	{
		fresh_elem->content = malloc(sizeof(*content) * content_size);
		ft_memcpy(fresh_elem->content, content, content_size);
		fresh_elem->content_size = content_size;
	}
	fresh_elem->next = NULL;
	return (fresh_elem);
}
