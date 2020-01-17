/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/28 10:56:09 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	bin_test_one_arg(char **tokens, int i)
{
	if (tokens[i])
		return (bin_test_return(0));
	return (bin_test_return(1));
}

static int	bin_test_two_arg(char **tokens, int i)
{
	int	flag;
	int	ret;

	flag = 0;
	if (ft_strequ(tokens[i], "!") && i)
		return (bin_test_error("", BIN_TEST_ERR_TM));
	if (ft_strequ(tokens[i], "!"))
		return (!bin_test_one_arg(tokens, 1));
	if (bin_test_get_unary(tokens[i], &flag))
	{
		ret = bin_test_unary(tokens[i + 1], flag);
		if (!i)
			return (bin_test_return(ret));
		return (ret);
	}
	return (bin_test_error(tokens[i], BIN_TEST_ERR_UN));
}

static int	bin_test_three_arg(char **tokens, int i)
{
	int	flag;
	int ret;

	flag = 0;
	if (bin_test_get_binary(tokens[i + 1], &flag))
	{
		ret = bin_test_binary(tokens[i], tokens[i + 2], flag);
		if (!i)
			return (bin_test_return(ret));
		return (ret);
	}
	if (ft_strequ(tokens[i], "!") && i)
		return (bin_test_error("", BIN_TEST_ERR_TM));
	if (ft_strequ(tokens[i], "!"))
	{
		ret = !bin_test_two_arg(tokens, 1);
		return (bin_test_return(ret));
	}
	return (bin_test_error(tokens[i + 1], BIN_TEST_ERR_BIN));
}

static int	bin_test_four_arg(char **tokens)
{
	int		ret;

	if (ft_strequ(tokens[0], "!"))
	{
		ret = !bin_test_three_arg(tokens, 1);
		return (bin_test_return(ret));
	}
	return (bin_test_error("", BIN_TEST_ERR_TM));
}

int			bin_test(char **tokens)
{
	int		count;

	ft_set_shell("?", "0");
	if (!tokens || !*tokens)
		return (bin_test_return(1));
	tokens++;
	if ((count = ft_calc_matr_rows(tokens)) == -1)
		return (bin_test_return(1));
	if (count == 0)
		return (bin_test_return(1));
	if (count == 1)
		return (bin_test_one_arg(tokens, 0));
	if (count == 2)
		return (bin_test_two_arg(tokens, 0));
	if (count == 3)
		return (bin_test_three_arg(tokens, 0));
	if (count == 4)
		return (bin_test_four_arg(tokens));
	return (bin_test_error("", BIN_TEST_ERR_TM));
}
