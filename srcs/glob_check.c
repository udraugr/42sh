/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:39:53 by wveta             #+#    #+#             */
/*   Updated: 2019/12/16 13:12:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	glob_btrack(char *str, char *b_str, char *b_pat)
{
	if (*str == 0 || !b_pat)
		return (false);
	return (glob_check(b_str + 1, b_pat, b_str + 1, b_pat));
}

static bool	glob_liter(char *str, char *pat, char *b_str, char *b_pat)
{
	if (*str == *pat)
	{
		if (*str == 0)
			return (true);
		return (glob_check(str + 1, pat + 1, b_str, b_pat));
	}
	return (glob_btrack(str, b_str, b_pat));
}

static bool	glob_quote(char *str, char *pat, char *b_str, char *b_pat)
{
	char	cmp;

	cmp = *pat++;
	while (*pat == *str && *pat != cmp)
	{
		str++;
		pat++;
	}
	if (*pat == cmp)
		return (glob_check(str, pat + 1, b_str, b_pat));
	if (*str && *pat && *str != *pat)
		return (glob_btrack(str, b_str, b_pat));
	return (glob_btrack(str, b_str, b_pat));
}

static bool	glob_class(char *str, char *pat, char *b_str, char *b_pat)
{
	bool	match;
	bool	exclam;
	char	*start;
	char	*end;

	match = false;
	exclam = (*pat == '!');
	start = pat + exclam;
	while (*start && *start != ']')
	{
		if (!(end = start))
			return (glob_liter(str, pat, b_str, b_pat));
		if (*(start + 1) == '-' && *(start + 2) != ']')
			if (!(end = start + 2))
				return (glob_liter(str, pat, b_str, b_pat));
		match |= (*start <= *str && *str <= *end);
		start = end + 1;
	}
	if (match == exclam)
		return (glob_btrack(str, b_str, b_pat));
	return (glob_check(str + 1, start + 1, b_str, b_pat));
}

bool		glob_check(char *str, char *pat, char *b_str, char *b_pat)
{
	if (*pat == '?' && *str == 0)
		return (false);
	if ((*pat == '*' && *(pat + 1) == 0) || (*pat == *str && !*str))
		return (true);
	if (*pat == '?')
		return (glob_check(str + 1, pat + 1, b_str, b_pat));
	if (*pat == '*')
		return (glob_check(str, pat + 1, str, pat + 1));
	if (*pat == '[')
		return (glob_class(str, pat + 1, b_str, b_pat));
	if (*pat == '\"' || *pat == '\'')
		return (glob_quote(str, pat, b_str, b_pat));
	if (*pat == '\\')
		pat++;
	return (glob_liter(str, pat, b_str, b_pat));
}
