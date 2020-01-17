/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_multiplicativ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:43:48 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:05:23 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

static void				error_found_division_by_zero(void)
{
	g_error_arithmetic = ft_strdup("division by 0");
}

static int32_t			calc(int32_t first, int32_t second, int32_t type)
{
	if ((type == DIVISION || type == MODULE) && second == 0)
	{
		error_found_division_by_zero();
		return (0);
	}
	if (type == DIVISION)
		return (first / second);
	else if (type == MODULE)
		return (first % second);
	else
		return (first * second);
}

int32_t					expr_multiplicativ(void)
{
	int32_t				ans;
	int32_t				tmp;
	int32_t				type;

	ans = expr_unar();
	if (g_error_arithmetic)
		return (0);
	while (g_lexem && g_lexem->content_size == OPER
		&&
			(
				((t_oper *)g_lexem->content)->id == MULTIPLICATION
				|| ((t_oper *)g_lexem->content)->id == DIVISION
				|| ((t_oper *)g_lexem->content)->id == MODULE))
	{
		type = ((t_oper *)g_lexem->content)->id;
		g_lexem = g_lexem->next;
		tmp = expr_unar();
		if (g_error_arithmetic)
			return (0);
		ans = calc(ans, tmp, type);
	}
	return (ans);
}
