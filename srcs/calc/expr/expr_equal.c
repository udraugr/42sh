/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_equal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:47:35 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:01:24 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					expr_equal(void)
{
	int32_t			ans;
	int32_t			type;

	ans = expr_relat_op();
	if (g_error_arithmetic)
		return (0);
	while (g_lexem && g_lexem->content_size == OPER
			&& (
				((t_oper *)g_lexem->content)->id == EQUAL
				|| ((t_oper *)g_lexem->content)->id == NOT_EQUAL))
	{
		type = ((t_oper *)g_lexem->content)->id;
		g_lexem = g_lexem->next;
		ans = (type == EQUAL) ?
				ans == expr_relat_op() : ans != expr_relat_op();
		if (g_error_arithmetic)
			return (0);
	}
	return (ans);
}
