/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexem_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 09:51:25 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:56:20 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

void				destroy_lexem(void *lexem, size_t type)
{
	if (lexem == 0)
		return ;
	if (type == OPER)
	{
		((t_oper *)lexem)->id = 0;
	}
	else if (type == VAR)
	{
		((t_var *)lexem)->value = 0;
		ft_strdel(&((t_var *)lexem)->name);
	}
	else if (type == NUMB)
	{
		((t_numb *)lexem)->numb = 0;
	}
	free(lexem);
}
