/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:01:23 by wveta             #+#    #+#             */
/*   Updated: 2019/12/13 11:08:36 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_TEST_H
# define BIN_TEST_H

# define BIN_TEST_UN_OPTIONS "bcdefghLnprSstuwxz"
# define BIN_TEST_ERR_BIN "binary operator expected"
# define BIN_TEST_ERR_UN "unary operator expected"
# define BIN_TEST_ERR_TM "too many argumanets"
# define BIN_TEST_ERR_INT "integer expression expected"
# define BIN_TEST_BLOCK (1)
# define BIN_TEST_CHAR (1 << 1)
# define BIN_TEST_DIR (1 << 2)
# define BIN_TEST_EXIST (1 << 3)
# define BIN_TEST_FILE (1 << 4)
# define BIN_TEST_GID (1 << 5)
# define BIN_TEST_SLNK_H (1 << 6)
# define BIN_TEST_SLNK_L (1 << 7)
# define BIN_TEST_STR_NZERO (1 << 8)
# define BIN_TEST_FIFO (1 << 9)
# define BIN_TEST_READ (1 << 10)
# define BIN_TEST_SOCKET (1 << 11)
# define BIN_TEST_SIZE_NZERO (1 << 12)
# define BIN_TEST_FD (1 << 13)
# define BIN_TEST_UID (1 << 14)
# define BIN_TEST_WRITE (1 << 15)
# define BIN_TEST_EXEC (1 << 16)
# define BIN_TEST_STR_ZERO (1 << 17)
# define BIN_TEST_STR_EQU (1 << 18)
# define BIN_TEST_STR_NEQU (1 << 19)
# define BIN_TEST_INT_EQU (1 << 20)
# define BIN_TEST_INT_NEQU (1 << 21)
# define BIN_TEST_INT_GT (1 << 22)
# define BIN_TEST_INT_GE (1 << 23)
# define BIN_TEST_INT_LT (1 << 24)
# define BIN_TEST_INT_LE (1 << 25)

int		bin_test(char **tokens);
int		bin_test_unary(char *arg, int flag);
int		bin_test_binary(char *arg1, char *arg2, int flag);
int		bin_test_get_unary(char *arg, int *flag);
int		bin_test_get_binary(char *arg, int *flag);
int		bin_test_error(char *var, char *message);
#endif
