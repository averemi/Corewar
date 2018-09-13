/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfil <vfil@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:51:05 by vfil              #+#    #+#             */
/*   Updated: 2018/07/17 18:51:07 by vfil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	clear_lifes(t_core *core)
{
	t_proc	*tmp;

	tmp = core->proc;
	while (tmp)
	{
		tmp->live = 0;
		tmp = tmp->next;
	}
}

void	del_proc(t_core *core)
{
	t_proc	*tmp;
	t_proc	*past;

	past = core->proc;
	while (past && past->next)
	{
		tmp = past->next;
		if (tmp->live == 0)
		{
			past->next = tmp->next;
			free(tmp);
		}
		else
			past = past->next;
	}
	if (core->proc->live == 0)
	{
		tmp = core->proc->next;
		free(core->proc);
		core->proc = tmp;
	}
	clear_lifes(core);
}

void	reset_lives(t_core *core)
{
	int		i;
	char	f;

	f = 0;
	i = 0;
	while (i < core->bots_count)
	{
		if (core->bots[i].live > NBR_LIVE && !f)
		{
			core->cycle_to_die -= CYCLE_DELTA;
			core->decycle = 1;
			f = 1;
		}
		core->bots[i].live = 0;
		i++;
	}
	if (core->checks == MAX_CHECKS)
	{
		if (!core->decycle)
			core->cycle_to_die -= CYCLE_DELTA;
		core->checks = 0;
		core->decycle = 0;
	}
	core->checks++;
}

void	count_life(t_core *core, int i)
{
	t_proc	*tmp;

	tmp = core->proc;
	while (tmp)
	{
		if (tmp->last_live > 0 && tmp->bot_id == i)
		{
			core->bots[i].live++;
			core->bots[i].last_life = tmp->last_live;
			tmp->last_live = 0;
		}
		tmp = tmp->next;
	}
}

void	check_life(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->bots_count)
	{
		count_life(core, i);
		i++;
	}
}
