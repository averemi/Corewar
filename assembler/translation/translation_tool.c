/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:12:22 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 12:12:23 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

unsigned int	reverse_bits(int num, int bytes, int sign)
{
	unsigned int	rev_num;
	unsigned char	*n1;
	unsigned char	*n2;

	sign = 0;
	n1 = (unsigned char *)&num;
	n2 = (unsigned char *)&rev_num;
	if (bytes == 4)
	{
		n2[0] = n1[3];
		n2[1] = n1[2];
		n2[2] = n1[1];
		n2[3] = n1[0];
	}
	else if (bytes == 2)
	{
		n2[0] = n1[1];
		n2[1] = n1[0];
	}
	return ((bytes != 1) ? rev_num : num);
}

int				ft_len_exec(t_parser *par)
{
	int res;

	res = 0;
	while (par)
	{
		if (par->type == COMMAND)
			res += par->size;
		par = par->next;
	}
	return (res);
}

static void		ft_set_header(int fd)
{
	int i;

	i = 0xf383ea << 8;
	write(fd, &i, 4);
}

void			ft_translation(int fd, t_parser *par)
{
	int i;
	int zero;

	i = -1;
	zero = 0;
	while (++i < 7)
	{
		if (!i)
			ft_set_header(fd);
		else if (i == 1)
			ft_set_name_com(fd, NAME, par);
		else if (i == 4)
			ft_set_name_com(fd, COMMENT, par);
		else if (i == 3)
			ft_set_len(fd, ft_len_exec(par));
		else if (i == 6)
			ft_set_exec(fd, par);
		else
			write(fd, &zero, 4);
	}
}
