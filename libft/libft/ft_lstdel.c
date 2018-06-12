/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:06:13 by galy              #+#    #+#             */
/*   Updated: 2016/11/20 17:09:39 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp_list;
	t_list	*tmp_next;

	tmp_list = *alst;
	while (tmp_list->next != NULL)
	{
		tmp_next = tmp_list->next;
		del(tmp_list->content, tmp_list->content_size);
		free(tmp_list);
		tmp_list = tmp_next;
	}
	del(tmp_list->content, tmp_list->content_size);
	free(tmp_list);
	*alst = NULL;
}
