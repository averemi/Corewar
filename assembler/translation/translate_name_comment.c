/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_name_comment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:11:33 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 12:11:34 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

void	ft_set_name_com(int fd, int op, t_parser *par)
{
	int i;
	int z;
	int zero;

	zero = 0;
	i = op == COMMENT ? 2048 : 128;
	z = 0;
	while (par)
	{
		if (op == par->type)
		{
			while (i--)
			{
				if (par->line[z])
					write(fd, &par->line[z++], 1);
				else
					write(fd, &zero, 1);
			}
		}
		par = par->next;
	}
}
