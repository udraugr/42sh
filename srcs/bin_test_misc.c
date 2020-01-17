/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_test_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/28 10:54:12 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			bin_test_error(char *var, char *message)
{
	if (message)
		ft_print_msg(message, var);
	ft_set_shell("?", "2");
	return (1);
}

int			bin_test_get_unary(char *arg, int *flag)
{
	int	shift;

	shift = 0;
	if (arg[0] != '-' || !arg[1] || arg[2])
		return (0);
	if ((shift = ft_strchrlen(BIN_TEST_UN_OPTIONS, arg[1])) == -1)
		return (0);
	*flag |= (1 << shift);
	return (1);
}

static int	bin_test_get_binary_return(int *flag, int shift)
{
	*flag |= shift;
	return (1);
}

int			bin_test_return(int code)
{
	if (code == 0)
		ft_set_shell("?", "0");
	else
		ft_set_shell("?", "1");
	return (1);
}

int			bin_test_get_binary(char *arg, int *flag)
{
	if (ft_strequ(arg, "="))
		return (bin_test_get_binary_return(flag, BIN_TEST_STR_EQU));
	if (ft_strequ(arg, "!="))
		return (bin_test_get_binary_return(flag, BIN_TEST_STR_NEQU));
	if (ft_strequ(arg, "-eq"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_EQU));
	if (ft_strequ(arg, "-ne"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_NEQU));
	if (ft_strequ(arg, "-gt"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_GT));
	if (ft_strequ(arg, "-ge"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_GE));
	if (ft_strequ(arg, "-lt"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_LT));
	if (ft_strequ(arg, "-le"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_LE));
	return (0);
}
