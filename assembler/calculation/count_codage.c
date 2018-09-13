/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_codage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:43:52 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 10:43:53 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static int		ft_transform_codage(int cod, int type)
{
	if (type == 1)
		return (cod | 64);
	else if (type == 2)
		return (cod | 192);
	else
		return (cod | 128);
}

void			ft_count_codage(t_parser *par)
{
	t_args	*tmp;
	int		i;

	while (par)
	{
		tmp = par->args;
		if (par->codage == 1)
		{
			par->codage = 0;
			i = 0;
			while (tmp)
			{
				par->codage = ft_transform_codage(par->codage, tmp->type_arg);
				tmp = tmp->next;
				if (tmp && ++i)
					par->codage = par->codage << 2;
			}
			while (i--)
				par->codage = par->codage >> 2;
		}
		par = par->next;
	}
}
