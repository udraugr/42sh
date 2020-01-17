/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexem_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:27:25 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:52:25 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

t_oper				*create_oper(int32_t id)
{
	t_oper			*new_oper;

	new_oper = (t_oper *)malloc(sizeof(t_oper));
	if (new_oper == NULL)
		return (NULL);
	new_oper->id = id;
	return (new_oper);
}

t_var				*create_var(char *name, int32_t value)
{
	t_var			*new_var;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->name = ft_strdup(name);
	new_var->value = value;
	return (new_var);
}

t_numb				*create_numb(int32_t number)
{
	t_numb			*new_numb;

	new_numb = (t_numb *)malloc(sizeof(t_numb));
	if (new_numb == NULL)
		return (NULL);
	new_numb->numb = number;
	return (new_numb);
}
