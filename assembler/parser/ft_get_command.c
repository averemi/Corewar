/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:46:39 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 10:46:39 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

int						ft_get_command(char *s, t_parser **par)
{
	int	i;

	i = 0;
	g_file++;
	(*par)->type = COMMAND;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i])
	{
		if (ft_strchr(s + i, LABEL_CHAR))
			return (ft_check_label(s + i, *par));
		else
			return (ft_parse_command(s + i, *par));
	}
	return (-1);
}
