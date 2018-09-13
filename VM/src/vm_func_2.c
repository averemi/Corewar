/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 16:48:15 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/15 16:48:17 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	vm_fork(t_core *core, t_proc *proc)
{
	short	pc;

	pc = (short)get_tdir(g_op_tab[cmd_id(proc->code)].label, core,
							(proc->pc + 1));
	add_proc(&core->proc, proc_copy(proc, core->maps.v_map,
									mod(proc->pc + IDX(pc))));
	proc->pc = MEM(proc->pc + 1 + g_op_tab[cmd_id(proc->code)].label);
	proc->code = core->maps.v_map[proc->pc];
	proc->cycles = g_op_tab[cmd_id(proc->code)].cycles;
}

void	vm_lld(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	unsigned char	*codage;

	if (check_codage(core, proc))
	{
		codage = get_codage(core->maps.v_map[MEM(proc->pc + 1)]);
		arg = get_args(core, proc, 0);
		if (codage[0] == T_IND)
			arg[0] = get_tdir(DIR_SIZE, core, (proc->pc +
								core->maps.v_map[MEM(proc->pc + 2)]));
		proc->reg[arg[1]] = arg[0];
		if (proc->reg[arg[1]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
		free(arg);
		free(codage);
	}
	move_proc(core, proc);
}

void	vm_lldi(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	unsigned int	*arg2;
	unsigned int	pos;
	unsigned char	*codage;

	if (check_codage(core, proc))
	{
		arg = get_args(core, proc, T_REG_VALUE);
		arg2 = get_args(core, proc, T_REG_NUMBER);
		codage = get_codage(core->maps.v_map[MEM(proc->pc + 1)]);
		if (codage[0] == T_DIR && codage[1] == T_DIR)
			pos = mod(proc->pc + (short)arg[0] + (short)arg[1]);
		else if (codage[0] == T_DIR)
			pos = mod(proc->pc + (short)arg[0] + (int)arg[1]);
		else if (codage[1] == T_DIR)
			pos = mod(proc->pc + (int)arg[0] + (short)arg[1]);
		else
			pos = mod(proc->pc + (int)arg[0] + (int)arg[1]);
		proc->reg[arg2[2]] = get_tdir(DIR_SIZE, core, pos);
		proc->carry = (proc->reg[arg2[2]] == 0) ? 1 : 0;
		free(arg);
		free(arg2);
		free(codage);
	}
	move_proc(core, proc);
}

void	vm_lfork(t_core *core, t_proc *proc)
{
	unsigned int	pc;

	pc = get_tdir(g_op_tab[cmd_id(proc->code)].label, core, (proc->pc + 1));
	add_proc(&core->proc, proc_copy(proc, core->maps.v_map,
									mod(proc->pc + (short)pc)));
	proc->pc = MEM((proc->pc + 1 + g_op_tab[cmd_id(proc->code)].label));
	proc->code = core->maps.v_map[proc->pc];
	proc->cycles = g_op_tab[cmd_id(proc->code)].cycles;
}

void	vm_aff(t_core *core, t_proc *proc)
{
	ft_printf("%c", (proc->reg[core->maps.v_map[MEM(proc->pc + 2)]] % 256));
	move_proc(core, proc);
}
