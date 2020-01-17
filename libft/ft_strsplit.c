/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:40:43 by wveta             #+#    #+#             */
/*   Updated: 2019/12/06 18:28:08 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		count;
	int		flag;
	int		i;

	count = 0;
	flag = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (flag == 1)
				flag = 0;
		}
		else if (flag == 0)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	ft_get_word(char **ret, int count, int size, char const *s)
{
	if (*(s + size) == '\0')
		size = size + 1;
	ret[count] = (char *)malloc(sizeof(char) * (size + 1));
	if (ret[count] == NULL)
		return (-1);
	ret[count][size + 0] = '\0';
	ret[count] = ft_strncpy(ret[count], s, (size_t)(size));
	return (0);
}

static int	ft_all_words(char **ret, char const *s, char c)
{
	int		flag;
	int		start;
	int		count;
	int		i;

	i = -1;
	count = -1;
	flag = 0;
	while (++i <= (int)ft_strlen(s))
	{
		if ((s[i] == c || s[i] == '\0') && (flag == 1))
		{
			flag = 0;
			if (ft_get_word(ret, count, i - start, s + start) == -1)
				return (-1);
		}
		else if (s[i] != c && s[i] != '\0' && flag == 0)
		{
			flag = 1;
			count++;
			start = i;
		}
	}
	return (0);
}

static void	ft_free_array(char **s)
{
	int i;

	if (s)
	{
		i = 0;
		if (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
}

char		**ft_strsplit(char const *s, char c)
{
	int		count;
	char	**ret;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (ret == NULL)
		return (NULL);
	else
	{
		ret[count] = NULL;
		if (ft_all_words(ret, s, c) == -1)
		{
			ft_free_array(ret);
			return (NULL);
		}
	}
	return (ret);
}
