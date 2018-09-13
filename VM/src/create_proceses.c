/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proceses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 10:09:38 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/09 10:09:40 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

unsigned int	count_proc(t_proc *proc)
{
	unsigned int	count;

	count = 0;
	while (proc)
	{
		count++;
		proc = proc->next;
	}
	return (count);
}

t_proc			*proc_copy(t_proc *curr_proc, unsigned char *map,
					unsigned int position)
{
	int		i;
	t_proc	*proc;

	i = 0;
	proc = (t_proc*)malloc(sizeof(t_proc));
	proc->pc = position;
	proc->bot_id = curr_proc->bot_id;
	proc->carry = curr_proc->carry;
	proc->code = map[position];
	proc->live = 0;
	proc->last_live = 0;
	while (i < REG_NUMBER + 1)
	{
		proc->reg[i] = curr_proc->reg[i];
		i++;
	}
	proc->cycles = g_op_tab[cmd_id(proc->code)].cycles + 1;
	proc->next = NULL;
	return (proc);
}

t_proc			*new_proc(unsigned int id, unsigned char *map,
					unsigned int position)
{
	int		i;
	t_proc	*proc;

	i = 2;
	proc = (t_proc*)malloc(sizeof(t_proc));
	proc->pc = position;
	proc->bot_id = id;
	proc->carry = 0;
	proc->code = map[position];
	proc->live = 0;
	proc->last_live = 0;
	proc->reg[1] = 0xffffffff - id;
	while (i < REG_NUMBER + 1)
	{
		proc->reg[i] = 0;
		i++;
	}
	proc->cycles = g_op_tab[cmd_id(proc->code)].cycles;
	proc->next = NULL;
	return (proc);
}

void			add_proc(t_proc **alst, t_proc *new)
{
	t_proc	*tmp;

	if (new && alst)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}

void			init_proceses(t_bot *bots, unsigned int bots_count,
								t_core *core)
{
	int		i;
	t_proc	*tmp;

	i = bots_count - 2;
	core->proc = new_proc(bots[bots_count - 1].id, core->maps.v_map,
					MEM_SIZE / bots_count * bots[bots_count - 1].id);
	tmp = core->proc;
	while (i >= 0)
	{
		tmp->next = new_proc(bots[i].id, core->maps.v_map,
				MEM_SIZE / bots_count * bots[i].id);
		tmp = tmp->next;
		i--;
	}
}
