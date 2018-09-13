/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 16:53:49 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/15 16:53:51 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	vm_add(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	unsigned char	reg_i;

	if (check_codage(core, proc))
	{
		arg = get_args(core, proc, T_REG_VALUE);
		reg_i = REG(core->maps.v_map[MEM(proc->pc + 4)]);
		proc->reg[reg_i] = arg[0] + arg[1];
		if (proc->reg[reg_i] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
		free(arg);
	}
	move_proc(core, proc);
}

void	vm_sub(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	unsigned char	reg_i;

	if (check_codage(core, proc))
	{
		arg = get_args(core, proc, T_REG_VALUE);
		reg_i = REG(core->maps.v_map[MEM(proc->pc + 4)]);
		proc->reg[reg_i] = arg[0] - arg[1];
		if (proc->reg[reg_i] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
		free(arg);
	}
	move_proc(core, proc);
}

void	vm_and(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	unsigned int	*reg_i;

	if (check_codage(core, proc))
	{
		arg = get_args(core, proc, T_REG_VALUE);
		reg_i = get_args(core, proc, T_REG_NUMBER);
		proc->reg[reg_i[2]] = arg[0] & arg[1];
		if (proc->reg[reg_i[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
		free(arg);
		free(reg_i);
	}
	move_proc(core, proc);
}

void	vm_or(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	unsigned int	*reg_i;

	if (check_codage(core, proc))
	{
		arg = get_args(core, proc, T_REG_VALUE);
		reg_i = get_args(core, proc, T_REG_NUMBER);
		proc->reg[reg_i[2]] = arg[0] | arg[1];
		if (proc->reg[reg_i[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
		free(arg);
		free(reg_i);
	}
	move_proc(core, proc);
}

void	vm_xor(t_core *core, t_proc *proc)
{
	unsigned int	*arg;
	unsigned int	*reg_i;

	if (check_codage(core, proc))
	{
		arg = get_args(core, proc, T_REG_VALUE);
		reg_i = get_args(core, proc, T_REG_NUMBER);
		proc->reg[reg_i[2]] = arg[0] ^ arg[1];
		if (proc->reg[reg_i[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
		free(arg);
		free(reg_i);
	}
	move_proc(core, proc);
}
