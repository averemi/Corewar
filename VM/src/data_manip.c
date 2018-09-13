/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:02:55 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/13 11:02:58 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int				cmd_id(unsigned char cmd)
{
	int i;

	i = 0;
	while (i < 17)
	{
		if (g_op_tab[i].code == cmd)
			return (i);
		i++;
	}
	return (16);
}

unsigned int	skip(int label, unsigned char cdg)
{
	unsigned int	size;
	unsigned char	c[3];
	int				i;

	size = 0;
	c[0] = cdg >> 6;
	c[1] = cdg << 2;
	c[1] = c[1] >> 6;
	c[2] = cdg << 4;
	c[2] = c[2] >> 6;
	i = 0;
	while (i < 3 && c[i])
	{
		if (c[i] == DIR_CODE)
			size += label;
		else if (c[i] == IND_CODE)
			size += 2;
		else
			size++;
		i++;
	}
	return (size);
}

unsigned int	get_tdir(int label, t_core *core, int pc)
{
	unsigned int	size;

	size = 0;
	if (label == 2)
	{
		size += core->maps.v_map[MEM(pc)] << 8;
		size += core->maps.v_map[MEM(pc + 1)];
	}
	else if (label == 4)
	{
		size += core->maps.v_map[MEM(pc)] << 24;
		size += core->maps.v_map[MEM(pc + 1)] << 16;
		size += core->maps.v_map[MEM(pc + 2)] << 8;
		size += core->maps.v_map[MEM(pc + 3)];
	}
	return (size);
}

void			put_on_map(t_core *core, int pc, unsigned int value,
							unsigned int id)
{
	unsigned char	c[5];
	int				i;

	c[0] = (unsigned char)(value >> 24);
	c[1] = (unsigned char)(value >> 16);
	c[2] = (unsigned char)(value >> 8);
	c[3] = (unsigned char)value;
	c[4] = '\0';
	i = 0;
	while (i < 4)
	{
		core->maps.v_map[MEM(pc + i)] = c[i];
		core->maps.c_map[MEM(pc + i)] = (unsigned char)(id);
		core->maps.c_cycle[MEM(pc + i)] = 50;
		i++;
	}
}

void			move_proc(t_core *core, t_proc *curr_proc)
{
	unsigned int	pc;

	if (core->maps.v_map[MEM(curr_proc->pc + 1)] < 64)
		pc = 0;
	else
		pc = skip(g_op_tab[cmd_id(curr_proc->code)].label,
					core->maps.v_map[curr_proc->pc + 1]);
	curr_proc->pc = MEM(curr_proc->pc + pc + 1 + 1);
	curr_proc->code = core->maps.v_map[curr_proc->pc];
	curr_proc->cycles = g_op_tab[cmd_id(curr_proc->code)].cycles;
}
