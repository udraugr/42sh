/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:01:08 by wveta             #+#    #+#             */
/*   Updated: 2019/12/25 17:34:37 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		fd_add_buf(t_list **buf, const int fd, char *work)
{
	t_list *new;

	if (!(fd > -1 && work))
		return (-1);
	new = ft_lstnew(work, ft_strlen(work) + 1);
	if (new == 0)
		return (-1);
	new->content_size = fd;
	ft_lstadd(buf, new);
	return (0);
}

static int		fd_free_buf(t_list **bufer, const int fd)
{
	t_list		*prev;
	t_list		*buf;

	prev = NULL;
	buf = *bufer;
	if (buf && fd > -1)
	{
		while (buf)
		{
			if (buf->content_size == (size_t)fd)
			{
				if (buf->content)
					free(buf->content);
				if (prev)
					prev->next = buf->next;
				else if (buf == *bufer)
					*bufer = buf->next;
				free(buf);
				return (0);
			}
			prev = buf;
			buf = prev->next;
		}
	}
	return (0);
}

static int		ft_cat_s(int t, int fd, char **line, t_block b)
{
	char	*s;
	int		pn;

	if (((s = *line) != *line) || (t == 0 && !(ft_strchr(s, (int)'\n'))) ||
		(t == 1 && !(ft_strchr((b.bl)->content, (int)'\n'))))
		return (t);
	if (t == 0 && (ft_strchr(s, (int)'\n')) &&
		(pn = (int)(ft_strchr(s, (int)'\n') - s)) > -1)
	{
		if ((s[pn + 1] != '\0') && (fd_add_buf(b.hd, fd, s + pn + 1) == -1))
			return (-1);
		s[pn] = '\0';
		return (1);
	}
	else if (t == 1 && ((pn = (ft_strchr((b.bl)->content, (int)'\n') -
		(char *)(b.bl)->content)) > -1))
	{
		*line = ft_strncpy(ft_strnew(pn), (b.bl)->content, pn);
		if (!(((ft_strchr((b.bl)->content, (int)'\0') - (char *)(b.bl)->
		content) - pn == 1) && ((fd_free_buf(b.hd, fd)) == 0)))
			(b.bl)->content = ft_strcpy((b.bl)->content,
			(b.bl)->content + pn + 1);
		return (0);
	}
	return (t);
}

static int		find_fd_list(const int fd, t_list **bufer, char **str)
{
	t_block	buf;

	buf.bl = *bufer;
	buf.hd = bufer;
	while (buf.bl)
		if (buf.bl->content_size == (size_t)fd)
		{
			if (*str)
				free(*str);
			if (!(ft_strchr(buf.bl->content, (int)'\n')))
			{
				if (!(*str = ft_strdup(buf.bl->content)))
					return (-1);
				fd_free_buf(bufer, fd);
				return (2);
			}
			else if (ft_cat_s(1, fd, str, buf) == 0)
				return (0);
		}
		else
			buf.bl = buf.bl->next;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*buf_list;
	char			buf[BUFF_SIZE + 1];
	int				rc;
	t_block			mls;

	while (!(fd < 0 || (line == NULL) || (read(fd, buf, 0) == -1)))
	{
		*line = NULL;
		mls.hd = &buf_list;
		if ((rc = find_fd_list(fd, &buf_list, line)) < 1)
			return (rc == -1 ? -1 : 1);
		while ((rc = read(fd, buf, BUFF_SIZE)) > -1000)
		{
			buf[rc] = '\0';
			if (rc < 0)
				return (-1);
			else if (rc == 0)
				return (rc + ((*line) ? 1 : 0));
			else if (rc > 0)
				if ((*line = ft_strfjoin(*line, buf)) &&
					(ft_cat_s(0, fd, line, mls) == 1))
					return (1);
		}
	}
	return (-1);
}
