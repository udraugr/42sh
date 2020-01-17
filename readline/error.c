/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 19:30:48 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 19:31:24 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		bad_fd_error(int fd, char *tmp)
{
	if (fd == 1)
		ft_print_msg(" : Error open STDOUT: ", tmp);
	else
		ft_print_msg(" : Error open STDERR: ", tmp);
	exit(EXIT_FAILURE);
}

void		mall_check(void)
{
	go_end_pos();
	ft_putstr_fd("ERROR: Cannot allocate memory.", STDERR_FILENO);
	return_func("\0", "exit");
}
