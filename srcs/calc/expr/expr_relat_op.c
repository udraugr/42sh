/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_relat_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:01:46 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:05:39 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

static int				calc(int32_t first, int32_t second, int32_t type)
{
	if (type == LESSER)
		return (first < second);
	else if (type == LE)
		return (first <= second);
	else if (type == GREATER)
		return (first > second);
	else
		return (first >= second);
}

int32_t					expr_relat_op(void)
{
	int32_t		ans;
	int32_t		tmp;
	int32_t		type;

	ans = expr_additive();
	if (g_error_arithmetic)
		return (0);
	while (g_lexem && g_lexem->content_size == OPER
			&&
			(
				((t_oper *)g_lexem->content)->id == LESSER
				|| ((t_oper *)g_lexem->content)->id == LE
				|| ((t_oper *)g_lexem->content)->id == GREATER
				|| ((t_oper *)g_lexem->content)->id == GE))
	{
		type = ((t_oper *)g_lexem->content)->id;
		g_lexem = g_lexem->next;
		tmp = expr_additive();
		if (g_error_arithmetic)
			return (0);
		ans = calc(ans, tmp, type);
	}
	return (ans);
}
