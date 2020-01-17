/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_unar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:58:44 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:06:11 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

static int32_t			calc(int32_t ans, int32_t type)
{
	if (type == MINUS)
		return (-ans);
	else
		return (ans);
}

int32_t					expr_unar(void)
{
	int32_t				ans;
	int32_t				type;

	ans = 1;
	while (g_lexem && g_lexem->content_size == OPER
			&&
			(
				((t_oper *)g_lexem->content)->id == PLUS
				|| ((t_oper *)g_lexem->content)->id == MINUS))
	{
		type = ((t_oper *)g_lexem->content)->id;
		g_lexem = g_lexem->next;
		ans = calc(ans, type);
	}
	ans = ans * expr_prefix();
	return (ans);
}
