/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:43:28 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:01:02 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					expr_and(void)
{
	int32_t				ans;

	ans = expr_equal();
	if (g_error_arithmetic)
		return (0);
	while (g_lexem && g_lexem->content_size == OPER &&
			((t_oper *)g_lexem->content)->id == AND)
	{
		g_lexem = g_lexem->next;
		ans = ans && expr_equal();
		if (g_error_arithmetic)
			return (0);
	}
	return (ans);
}
