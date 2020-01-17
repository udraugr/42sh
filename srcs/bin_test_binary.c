/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_test_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/28 10:53:05 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	bin_test_binary_checkint(char *arg)
{
	if (ft_isnumber(arg))
		return (1);
	ft_print_msg(BIN_TEST_ERR_INT, arg);
	return (0);
}

static int	bin_test_binary_int(int num1, int num2, int flag)
{
	if (flag & BIN_TEST_INT_EQU)
		return (!(num1 == num2));
	if (flag & BIN_TEST_INT_NEQU)
		return (!(num1 != num2));
	if (flag & BIN_TEST_INT_GT)
		return (!(num1 > num2));
	if (flag & BIN_TEST_INT_GE)
		return (!(num1 >= num2));
	if (flag & BIN_TEST_INT_LT)
		return (!(num1 < num2));
	if (flag & BIN_TEST_INT_LE)
		return (!(num1 <= num2));
	return (1);
}

int			bin_test_binary(char *arg1, char *arg2, int flag)
{
	int	num1;
	int num2;

	if (flag & BIN_TEST_STR_EQU)
		return (!ft_strcmp(arg1, arg2) ? 0 : 1);
	if (flag & BIN_TEST_STR_NEQU)
		return (!ft_strcmp(arg1, arg2) ? 1 : 0);
	if (!bin_test_binary_checkint(arg1))
		return (2);
	if (!bin_test_binary_checkint(arg2))
		return (2);
	num1 = ft_atoi(arg1);
	num2 = ft_atoi(arg2);
	return (bin_test_binary_int(num1, num2, flag));
}
