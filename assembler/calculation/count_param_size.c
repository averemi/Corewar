/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_param_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:45:46 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 10:45:47 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static int		ft_get_total(t_args *tmp, int res)
{
	if (!tmp)
		return (res);
	return (ft_get_total(tmp->next, res + tmp->arg_size));
}

void			ft_get_param_size(t_parser *par)
{
	while (par)
	{
		if (par->type == COMMAND && par->op)
			par->size = ft_get_total(par->args, 1 + (par->codage ? 1 : 0));
		par = par->next;
	}
}
