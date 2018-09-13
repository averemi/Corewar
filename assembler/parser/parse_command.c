/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:47:34 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 10:47:34 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static int				ft_check_coma(char *s)
{
	int i;
	int err;

	i = -1;
	err = 0;
	while (s[++i])
	{
		if (err == 2)
			return (ft_error(13));
		if (s[i] == SEPARATOR_CHAR)
			err++;
		else
			err = 0;
	}
	return (s[i - 1] == ',' ? ft_error(13) : 0);
}

static int				ft_parse_param(char *s, t_parser *par)
{
	int		i;
	int		j;
	char	**split;

	i = -1;
	if (ft_check_coma(s))
		return (-1);
	split = ft_strsplit(s, SEPARATOR_CHAR);
	while (split[++i])
	{
		j = 0;
		while (split[i][j] == ' ' || split[i][j] == '\t')
			j++;
		if (split[i][j] == 'r' && !ft_validate_reg(i, par, split[i] + j))
			;
		else if (split[i][j] == '%' && !ft_validate_dir(i, par, split[i] + j))
			;
		else if ((split[i][j] == ':' || ft_isdigit(split[i][j]) ||\
			split[i][j] == '-') && !ft_validate_ind(i, par, split[i] + j))
			;
		else
			return (ft_error(11));
	}
	ft_free_split(split);
	return (i > 3 || ft_check_under(i, par->op) ? ft_error(12) : 0);
}

static int				ft_parse_command3(char *s, t_parser *par, int *err)
{
	int i;

	i = 1;
	if (ft_strnstr(s, "or", 2) && ST(2) && (par->op = 7))
		i = ft_parse_param(s + 2, par);
	else if (ft_strnstr(s, "xor", 3) && ST(3) && (par->op = 8))
		i = ft_parse_param(s + 3, par);
	else if (ft_strnstr(s, "zjmp", 4) && ST(4) && (par->op = 9))
	{
		par->codage = 0;
		i = ft_parse_param(s + 4, par);
	}
	else if (ft_strnstr(s, "fork", 4) && ST(4) && (par->op = 12))
	{
		par->codage = 0;
		i = ft_parse_param(s + 4, par);
	}
	else if (ft_strnstr(s, "lldi", 4) && ST(4) && (par->op = 14))
		i = ft_parse_param(s + 4, par);
	else if (ft_strnstr(s, "lld", 3) && ST(3) && (par->op = 13))
		i = ft_parse_param(s + 3, par);
	*err = i == -1 ? -1 : *err;
	return (i);
}

static int				ft_parse_command2(char *s, t_parser *par, int *err)
{
	int i;

	i = 1;
	if (ft_strnstr(s, "live", 4) && ST(4) && (par->op = 1))
	{
		par->codage = 0;
		i = ft_parse_param(s + 4, par);
	}
	else if (ft_strnstr(s, "ldi", 3) && ST(3) && (par->op = 10))
		i = ft_parse_param(s + 3, par);
	else if (ft_strnstr(s, "sti", 3) && ST(3) && (par->op = 11))
		i = ft_parse_param(s + 3, par);
	else if (ft_strnstr(s, "ld", 2) && ST(2) && (par->op = 2))
		i = ft_parse_param(s + 2, par);
	else if (ft_strnstr(s, "st", 2) && ST(2) && (par->op = 3))
		i = ft_parse_param(s + 2, par);
	else if (ft_strnstr(s, "add", 3) && ST(3) && (par->op = 4))
		i = ft_parse_param(s + 3, par);
	else if (ft_strnstr(s, "sub", 3) && ST(3) && (par->op = 5))
		i = ft_parse_param(s + 3, par);
	else if (ft_strnstr(s, "and", 3) && ST(3) && (par->op = 6))
		i = ft_parse_param(s + 3, par);
	*err = i == -1 ? -1 : *err;
	return (i);
}

int						ft_parse_command(char *s, t_parser *par)
{
	int	err;

	err = 0;
	par->codage = 1;
	if (ft_parse_command2(s, par, &err) != 1)
		;
	else if (ft_parse_command3(s, par, &err) != 1)
		;
	else if (ft_strnstr(s, "lfork", 5) && ST(5) && (par->op = 15))
	{
		par->codage = 0;
		err = ft_parse_param(s + 5, par);
	}
	else if (ft_strnstr(s, "aff", 3) && ST(3) && (par->op = 16))
		err = ft_parse_param(s + 3, par);
	else
		return (ft_error(10));
	g_label = 0;
	return (err ? -1 : 0);
}
