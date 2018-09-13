/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:01:17 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 12:01:18 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static int						ft_valid_param(int type, int op, int num)
{
	static const int	map[16][3] = {{2, 0, 0}, {6, 1, 0}, {1, 7, 0},
	{1, 1, 1}, {1, 1, 1}, {4, 4, 1}, {4, 4, 1}, {4, 4, 1}, {2, 0, 0},
	{4, 5, 1}, {1, 4, 5}, {2, 0, 0}, {6, 1, 0}, {4, 5, 1}, {2, 0, 0},
	{1, 0, 0}};

	if (map[op - 1][num] == type || map[op - 1][num] == 4)
		return (0);
	else if (type == 1 && (map[op - 1][num] == 5 || map[op - 1][num] == 7))
		return (0);
	else if (type == 2 && (map[op - 1][num] == 5 || map[op - 1][num] == 6))
		return (0);
	else if (type == 3 && (map[op - 1][num] == 6 || map[op - 1][num] == 7))
		return (0);
	else
		return (-1);
}

static int						ft_get_dir_size(int op, int res)
{
	if ((op >= 9 && op <= 12) || (op >= 14 && op <= 15))
		return (res * -1);
	return (res);
}

int								ft_validate_reg(int num, t_parser *par, char *s)
{
	int	i;

	i = -1;
	if (num > 2 || !s[1])
		return (-1);
	while (s[++i])
	{
		if (i == 1 && !ft_isdigit(s[i]))
			return (-1);
		else if (i == 2 && (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t'))
			return (-1);
		if (i > 2 && (s[i] != ' ' && s[i] != '\t'))
			return (-1);
	}
	if (ft_valid_param(1, par->op, num))
		return (-1);
	ft_new_arg(&par->args, NULL, ft_atoi(s + 1), 1);
	return (0);
}

int								ft_validate_dir(int num, t_parser *par, char *s)
{
	int i;

	i = 0;
	if (s[1] == ':')
	{
		par->par = 1;
		if (ft_validate_label(s + 2, ft_strlen(s) - 2, 1))
			return (-1);
		if (ft_valid_param(2, par->op, num))
			return (-1);
		ft_new_arg(&par->args, s + 2, 0, ft_get_dir_size(par->op, 4));
	}
	else if (s[1])
	{
		i = s[i + 1] == '-' && ft_isdigit(s[i + 2]) ? i + 1 : i;
		while (s[++i])
			if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t')
				return (-1);
		if (ft_valid_param(2, par->op, num))
			return (-1);
		ft_new_arg(&par->args, 0, ft_atoi(s + 1), ft_get_dir_size(par->op, 3));
	}
	else
		return (-1);
	return (0);
}

int								ft_validate_ind(int num, t_parser *par, char *s)
{
	int i;

	i = -1;
	if (s[0] == '-' && ft_isdigit(s[1]))
		i++;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t')
			break ;
	if (ft_strlen(s) == (size_t)i)
	{
		if (ft_valid_param(3, par->op, num))
			return (-1);
		ft_new_arg(&par->args, NULL, ft_atoi(s), 2);
	}
	else
	{
		par->par = 1;
		if (ft_validate_label(s + 1, ft_strlen(s) - 1, 1) || s[0] == '-')
			return (-1);
		if (ft_valid_param(3, par->op, num))
			return (-1);
		ft_new_arg(&par->args, s + 1, 0, 2);
	}
	return (0);
}
