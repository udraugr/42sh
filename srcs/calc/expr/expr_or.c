/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:42:11 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:03:21 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					expr_or(void)
{
	int32_t				ans;

	ans = expr_and();
	if (g_error_arithmetic)
		return (0);
	while (g_lexem && g_lexem->content_size == OPER &&
			((t_oper *)g_lexem->content)->id == OR)
	{
		g_lexem = g_lexem->next;
		ans = expr_and() || ans;
		if (g_error_arithmetic)
			return (0);
	}
	return (ans);
}
