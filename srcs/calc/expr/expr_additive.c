/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_additive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:38:35 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:01:56 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					expr_additive(void)
{
	int32_t			ans;
	int32_t			type;

	ans = expr_multiplicativ();
	if (g_error_arithmetic)
		return (0);
	while (g_lexem && g_lexem->content_size == OPER
			&&
			(
				((t_oper *)g_lexem->content)->id == PLUS
				|| ((t_oper *)g_lexem->content)->id == MINUS))
	{
		type = ((t_oper *)g_lexem->content)->id;
		g_lexem = g_lexem->next;
		ans = (type == PLUS) ?
			ans + expr_multiplicativ() : ans - expr_multiplicativ();
		if (g_error_arithmetic)
			return (0);
	}
	return (ans);
}
