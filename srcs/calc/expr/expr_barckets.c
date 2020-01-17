/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_barckets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 09:41:19 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:02:58 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					expr_barckets(void)
{
	int32_t				ans;

	if (g_lexem && g_lexem->content_size == OPER
		&& ((t_oper *)g_lexem->content)->id == LBRACE)
	{
		g_lexem = g_lexem->next;
		ans = expr();
		if (g_error_arithmetic)
			return (0);
		if (g_lexem && g_lexem->content_size == OPER &&
			((t_oper *)g_lexem->content)->id == RBRACE)
		{
			g_lexem = g_lexem->next;
		}
		else
		{
			syntax_error_found();
			return (0);
		}
		return (ans);
	}
	ans = expr_return_value();
	if (g_error_arithmetic)
		return (0);
	return (ans);
}
