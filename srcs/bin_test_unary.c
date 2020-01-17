/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_test_unary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/11/28 10:54:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	bin_test_unary_fd(char *arg1)
{
	int		num;

	if (!ft_isnumber(arg1))
		return (1);
	num = ft_atoi(arg1);
	return (fcntl(num, F_GETFL) == -1);
}

static int	bin_test_unary_type(t_stat stat, int flag)
{
	if (flag & BIN_TEST_BLOCK)
		return (S_ISBLK(stat.st_mode) ? 0 : 1);
	if (flag & BIN_TEST_SIZE_NZERO)
		return (stat.st_size != 0 ? 0 : 1);
	if (flag & BIN_TEST_CHAR)
		return (S_ISCHR(stat.st_mode) ? 0 : 1);
	if (flag & BIN_TEST_DIR)
		return (S_ISDIR(stat.st_mode) ? 0 : 1);
	if (flag & BIN_TEST_FILE)
		return (S_ISREG(stat.st_mode) ? 0 : 1);
	if (flag & BIN_TEST_SLNK_H || flag & BIN_TEST_SLNK_L)
		return (S_ISLNK(stat.st_mode) ? 0 : 1);
	if (flag & BIN_TEST_FIFO)
		return (S_ISFIFO(stat.st_mode) ? 0 : 1);
	if (flag & BIN_TEST_SOCKET)
		return (S_ISSOCK(stat.st_mode) ? 0 : 1);
	if (flag & BIN_TEST_GID)
		return (stat.st_mode & S_ISGID ? 0 : 1);
	if (flag & BIN_TEST_UID)
		return (stat.st_mode & S_ISUID ? 0 : 1);
	return (1);
}

int			bin_test_unary(char *arg1, int flag)
{
	t_stat	stat;

	if (flag & BIN_TEST_STR_NZERO)
		return (arg1 && *arg1 ? 0 : 1);
	if (flag & BIN_TEST_STR_ZERO)
		return (arg1 && !*arg1 ? 0 : 1);
	if (flag & BIN_TEST_FD)
		return (bin_test_unary_fd(arg1));
	if (lstat(arg1, &stat) == -1)
		return (1);
	if (flag & BIN_TEST_EXIST)
		return (0);
	if (flag & BIN_TEST_READ)
		return (stat.st_mode & S_IRUSR ? 0 : 1);
	if (flag & BIN_TEST_WRITE)
		return (stat.st_mode & S_IWUSR ? 0 : 1);
	if (flag & BIN_TEST_EXEC)
		return (stat.st_mode & S_IXUSR ? 0 : 1);
	return (bin_test_unary_type(stat, flag));
}
