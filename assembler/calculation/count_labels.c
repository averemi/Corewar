/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:44:34 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 10:44:35 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static char			*ft_del_space(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == ' ' || s[i] == '\t')
			s[i] = '\0';
	return (s);
}

static int			ft_get_path_after(const char *s, t_parser *par)
{
	int		res;
	t_label	*tmp;

	res = 0;
	while (par)
	{
		tmp = par->label;
		while (tmp)
		{
			if (!ft_strncmp((char *)s, tmp->name, ft_strcmp(s, tmp->name)\
				< 0 ? ft_strlen(tmp->name) : ft_strlen(s)))
				return (res);
			tmp = tmp->next;
		}
		res += par->size;
		par = par->next;
	}
	return (-1);
}

static int			ft_get_path(const char *s, int pos, t_parser *par)
{
	t_label	*tmp;
	int		i;
	int		fl;
	int		res;

	i = -1;
	fl = 0;
	res = 0;
	while (par && ++i > -1)
	{
		tmp = par->label;
		while (!fl && tmp)
		{
			if (!ft_strncmp((char *)s, tmp->name, ft_strcmp(s, tmp->name)\
				< 0 ? ft_strlen(tmp->name) : ft_strlen(s)))
				fl = 1;
			tmp = tmp->next;
		}
		if (fl && i < pos)
			res += par->size;
		if (i == pos)
			break ;
		par = par->next;
	}
	return (fl ? res * -1 : ft_get_path_after(s, par));
}

int					ft_count_labels(t_parser *head)
{
	int			i;
	t_args		*tmp;
	t_parser	*par;

	par = head;
	i = -1;
	while (par && ++i > -1)
	{
		tmp = par->args;
		if (par->par)
			while (tmp)
			{
				if (tmp->val)
				{
					if ((tmp->value = \
					ft_get_path(ft_del_space(tmp->val), i, head)) == -1)
						return (ft_error(15));
					free(tmp->val);
					tmp->val = NULL;
				}
				tmp = tmp->next;
			}
		par = par->next;
	}
	return (0);
}
