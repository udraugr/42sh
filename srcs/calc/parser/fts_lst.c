/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:26:45 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/21 12:14:20 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

t_list				*lst_create(void *content, size_t type)
{
	t_list			*new;

	if ((new = (t_list *)malloc(sizeof(t_list))) == 0)
		return (0);
	new->next = 0;
	new->content = content;
	new->content_size = type;
	return (new);
}

void				lst_del(t_list **lst, void (*f)(void *, size_t))
{
	t_list			*tmp;
	t_list			*del;

	if (!lst && !*lst)
		return ;
	tmp = *lst;
	*lst = 0;
	while (tmp)
	{
		if (tmp->content)
			f(tmp->content, tmp->content_size);
		tmp->content = 0;
		del = tmp;
		tmp = tmp->next;
		ft_memdel((void **)&del);
	}
}
