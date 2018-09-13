/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 14:23:02 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/21 14:23:04 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	vm_live(t_core *core, t_proc *curr_proc)
{
	unsigned int	tdir;

	tdir = get_tdir(g_op_tab[cmd_id(curr_proc->code)].label, core,
					(curr_proc->pc + 1));
	curr_proc->live = 1;
	if ((0xffffffff - tdir) == (unsigned int)curr_proc->bot_id)
	{
		core->maps.c_map[MEM(curr_proc->pc)] =
				(unsigned char)(curr_proc->bot_id + 1);
		core->maps.c_cycle[MEM(curr_proc->pc)] = 50;
		curr_proc->last_live = core->cycle + 1;
	}
	curr_proc->live = 1;
	curr_proc->pc += 1 + 4;
	curr_proc->code = core->maps.v_map[curr_proc->pc];
	curr_proc->cycles = g_op_tab[cmd_id(curr_proc->code)].cycles;
}

void	vm_undef(t_core *core, t_proc *curr_proc)
{
	curr_proc->pc = MEM(curr_proc->pc + 1);
	curr_proc->code = core->maps.v_map[curr_proc->pc];
	curr_proc->cycles = g_op_tab[cmd_id(curr_proc->code)].cycles;
}
