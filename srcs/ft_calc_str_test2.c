/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_str_test2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:14:54 by wveta             #+#    #+#             */
/*   Updated: 2019/12/03 12:33:49 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_test_doll_calc(t_quoteflag *f, char **str)
{
	if (f->qflag == 0 &&
	f->br_flag == 0 &&
	(f->i == 0 || f->b_sl == 0) &&
	str[f->n][f->i] == '$' &&
	str[f->n][f->i + 1] &&
	str[f->n][f->i + 1] == '(')
		f->start = f->i + 1;
}

void		ft_set_b_sl(t_quoteflag *f, char **str)
{
	if (f->qflag != 2 && str[f->n][f->i] == '\\' && ((f->b_sl = f->b_sl + 1)))
		f->b_sl = f->b_sl % 2;
}
