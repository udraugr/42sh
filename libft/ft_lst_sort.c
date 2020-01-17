/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 13:13:41 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 15:33:03 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*merge(t_list *a, t_list *b, int (*cmp)())
{
	t_list		*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (cmp(a->content, b->content) < 0)
	{
		result = a;
		result->next = merge(a->next, b, cmp);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next, cmp);
	}
	return (result);
}

static void		split(t_list *source, t_list **right, t_list **left)
{
	t_list		*fast;
	t_list		*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*right = source;
	*left = slow->next;
	slow->next = NULL;
}

void			ft_lst_sort(t_list **alist, int (*cmp)())
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	head = *alist;
	if (!head || !(head->next))
		return ;
	split(head, &a, &b);
	ft_lst_sort(&a, cmp);
	ft_lst_sort(&b, cmp);
	*alist = merge(a, b, cmp);
}
