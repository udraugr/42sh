/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_numb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 20:04:27 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:54:59 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

static int32_t		is_digit(char c, int32_t base)
{
	char			*digits;
	int32_t			i;

	digits = "0123456789ABCDEF\0";
	i = 0;
	while (i < base)
	{
		if (c == digits[i] || (i >= 10 && c == digits[i] + 32))
			return (i);
		++i;
	}
	return (-1);
}

int32_t				ft_atoi_base(char *str, int32_t base, uint32_t *len_numb)
{
	int32_t			ans;

	ans = 0;
	if (base == 16)
		*len_numb += 2;
	else if (base == 8)
		++(*len_numb);
	while (*str && is_digit(*str, base) >= 0)
	{
		ans = ans * base + is_digit(*str, base);
		++(*len_numb);
		++str;
	}
	if (*len_numb > 15 && !g_correct_values)
	{
		ft_putendl_fd("Incorect values", 2);
		g_correct_values = !g_correct_values;
	}
	return (ans);
}

int32_t				it_number(char *str, t_list **lexem)
{
	int32_t			numb;
	uint32_t		len_numb;
	t_numb			*new_numb;
	t_list			*new;

	len_numb = 0;
	if (ft_strncmp("0x", str, 2) == 0)
		numb = ft_atoi_base(str + 2, 16, &len_numb);
	else if (ft_strncmp("0", str, 1) == 0)
		numb = ft_atoi_base(str + 1, 8, &len_numb);
	else
		numb = ft_atoi_base(str, 10, &len_numb);
	new_numb = create_numb(numb);
	new = lst_create((void *)new_numb, NUMB);
	ft_lstadd_last(lexem, new);
	new_numb = 0;
	return (len_numb);
}
