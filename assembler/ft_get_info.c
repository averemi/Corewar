/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:41:57 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 10:42:02 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_delete_comment(char *s)
{
	int i;
	int mark;
	int qu;

	i = -1;
	mark = 0;
	qu = 0;
	while (s[++i])
	{
		if (!mark && s[i] == '"')
			qu = !qu ? 1 : 0;
		if (!qu && (s[i] == '#' || s[i] == ';'))
			mark++;
		if (mark)
			s[i] = '\0';
	}
}

int			ft_get_info(t_parser *par, char **line)
{
	int	fl;

	fl = 0;
	while (get_next_line(g_fd, line) > 0)
	{
		ft_delete_comment(*line);
		if (*line[0] == '\0' || ft_find_end(0, *line))
		{
			g_last_line = 0;
			free(*line);
			continue ;
		}
		else if (ft_get_name_com(*line, par, &fl))
			return (-1);
		else if (!fl && ft_get_command(*line, &par))
			return (-1);
		free(*line);
		fl = 0;
		if (g_label)
			continue ;
		par->next = ft_new_par();
		par = par->next;
	}
	close(g_fd);
	return (g_last_line && ft_error(16) ? -1 : 0);
}
