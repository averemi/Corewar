/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:09:49 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 12:09:52 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

static void	ft_set_param(int fd, t_args *arg)
{
	if (!arg)
		return ;
	if (arg->value >= 0)
		arg->value = reverse_bits(arg->value, arg->arg_size, 0);
	else
		arg->value = reverse_bits(arg->value, arg->arg_size, 1);
	write(fd, &arg->value, arg->arg_size);
	ft_set_param(fd, arg->next);
}

void		ft_set_exec(int fd, t_parser *par)
{
	if (!par)
		return ;
	if (par->type == COMMAND && par->op)
	{
		write(fd, &par->op, 1);
		if (par->codage)
			write(fd, &par->codage, 1);
		ft_set_param(fd, par->args);
	}
	ft_set_exec(fd, par->next);
}
