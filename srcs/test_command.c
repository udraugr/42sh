/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:48:28 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/11 09:49:38 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int			main(void)
{
	int		i;
	char	buffer[4096];

	while (1)
	{
		buffer[0] = '\0';
		i = read(STDIN_FILENO, buffer, 4095);
		if (i > 0)
			write(STDOUT_FILENO, buffer, i);
		else if (i == 0)
		{
			write(STDOUT_FILENO, "\n EOF", 5);
			return (0);
		}
		else
		{
			write(STDOUT_FILENO, "\n READ ERROR", 12);
			return (1);
		}
	}
}
