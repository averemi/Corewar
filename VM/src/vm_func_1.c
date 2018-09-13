/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfil <vfil@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:32:12 by vfil              #+#    #+#             */
/*   Updated: 2018/07/09 19:32:14 by vfil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	vm_ld(t_core *core, t_proc *proc)
{
	unsigned int	*arg;

	if (check_codage(core, proc))
	{
		arg = get_args(core, proc, T_REG_NUMBER);
		proc->reg[arg[1]] = arg[0];
		if (proc->reg[arg[1]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
		free(arg);
	}
	move_proc(core, proc);
}

void	vm_st(t_core *core, t_proc *proc)
{
	unsigned char	*codage;
	unsigned int	*arg;
	int				buf;

	if (check_codage(core, proc))
	{
		codage = get_codage(core->maps.v_map[MEM(proc->pc + 1)]);
		arg = get_args(core, proc, T_REG_NUMBER);
		if (codage[1] == REG_CODE)
		{
			proc->reg[arg[1]] = proc->reg[arg[0]];
			move_proc(core, proc);
		}
		else
		{
			buf = proc->pc;
			move_proc(core, proc);
			put_on_map(core, mod(buf + IDX((short)get_tdir(2, core, buf + 3))),
						proc->reg[arg[0]], proc->bot_id + 1);
		}
		free(codage);
		free(arg);
	}
	else
		move_proc(core, proc);
}

void	vm_zjmp(t_core *core, t_proc *proc)
{
	short	pc;

	if (proc->carry)
		pc = (short)get_tdir(g_op_tab[cmd_id(proc->code)].label,
					core, (proc->pc + 1));
	else
		pc = 3;
	proc->pc = mod(proc->pc + pc % IDX_MOD);
	proc->code = core->maps.v_map[proc->pc];
	proc->cycles = g_op_tab[cmd_id(proc->code)].cycles;
}

void	vm_ldi(t_core *core, t_proc *proc)
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
			pos = mod(proc->pc + IDX((short)arg[0] + (short)arg[1]));
		else if (codage[0] == T_DIR)
			pos = mod(proc->pc + IDX((short)arg[0] + (int)arg[1]));
		else if (codage[1] == T_DIR)
			pos = mod(proc->pc + IDX((int)arg[0] + (short)arg[1]));
		else
			pos = mod(proc->pc + IDX((int)arg[0] + (int)arg[1]));
		proc->reg[arg2[2]] = get_tdir(DIR_SIZE, core, pos);
		free(arg);
		free(arg2);
		free(codage);
	}
	move_proc(core, proc);
}

void	vm_sti(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	int				pos;
	unsigned char	*codage;

	if (check_codage(core, proc))
	{
		codage = get_codage(core->maps.v_map[MEM(proc->pc + 1)]);
		arg = get_args(core, proc, T_REG_VALUE);
		if (codage[1] == DIR_CODE && codage[2] == DIR_CODE)
			pos = mod(proc->pc + IDX((short)arg[1] + (short)arg[2]));
		else if (codage[1] == DIR_CODE)
			pos = mod(proc->pc + IDX((int)((short)arg[1] + arg[2])));
		else if (codage[2] == DIR_CODE)
			pos = mod(proc->pc + IDX((int)(arg[1] + (short)arg[2])));
		else
			pos = mod(proc->pc + IDX((int)arg[1] + (int)arg[2]));
		move_proc(core, proc);
		put_on_map(core, pos, arg[0], proc->bot_id + 1);
		free(codage);
		free(arg);
	}
	else
		move_proc(core, proc);
}
