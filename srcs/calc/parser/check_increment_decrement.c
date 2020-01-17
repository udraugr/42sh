/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_increment_decrement.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:48:45 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:50:06 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

static int32_t		check_suffix(char *str, int len_oper)
{
	return (is_it_var(str + len_oper, 0));
}

static int32_t		check_prefix(t_list **lexem)
{
	t_list			*last;
	t_list			*pre_last;

	if (!lexem || !*lexem)
		return (FAIL);
	last = *lexem;
	pre_last = 0;
	while (last->next)
	{
		pre_last = last;
		last = last->next;
	}
	if (last->content_size == VAR)
	{
		if (pre_last && pre_last->content_size == OPER
				&& (((t_oper *)pre_last->content)->id == INCREMENT
						|| ((t_oper *)pre_last->content)->id == DECREMENT))
			return (FAIL);
		return (SUCCESS);
	}
	return (FAIL);
}

void				check_increment_decrement(char *str, t_list **lexem,
											uint32_t *id, uint32_t *len_oper)
{
	int32_t			suffix;
	int32_t			prefix;

	suffix = check_suffix(str, *len_oper);
	prefix = check_prefix(lexem);
	if (suffix == FAIL && prefix == FAIL)
	{
		*id += 2;
		*len_oper -= 1;
	}
}
