/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 18:34:44 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/05 18:34:45 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	update_colors(t_core *core)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (core->maps.c_cycle[i] > 0)
			core->maps.c_cycle[i]--;
		i++;
	}
}

char	update_proc(t_core *core, t_vm_func *vm_func)
{
	t_proc		*tmp;

	tmp = core->proc;
	update_colors(core);
	while (tmp)
	{
		if (tmp->cycles == 1)
			vm_func[cmd_id(tmp->code)](core, tmp);
		else
			tmp->cycles--;
		tmp = tmp->next;
	}
	check_life(core);
	core->cycle++;
	if (core->cycle > 1 && (core->cycle == core->new_reset))
	{
		reset_lives(core);
		del_proc(core);
		core->new_reset += core->cycle_to_die;
		if (core->cycle_to_die <= 0 || !count_proc(core->proc))
			return (1);
	}
	if (!core->flag.v && core->flag.d > 0 && core->flag.d == core->cycle)
		return (1);
	return (0);
}

void	input(unsigned int *speed, char *pause, char *s)
{
	int input;

	input = getch();
	if (input == 'q' && *speed > 10)
		*speed -= 10;
	else if (input == 'w' && *speed > 1)
		*speed -= 1;
	else if (input == 'e' && *speed < 1000)
		*speed += 1;
	else if (input == 'r' && *speed <= 990)
		*speed += 10;
	else if (input == ' ')
		*pause = (*pause == 0) ? 1 : 0;
	else if (input == 's')
		*s = 1;
}

void	run(t_core core, t_vm_func *vm_func)
{
	t_wind	*wnd;
	t_var	v;

	v.s = 0;
	v.pause = 0;
	v.speed = 50;
	v.end = 0;
	wnd = NULL;
	if (core.flag.v)
		wnd = init();
	while (!v.end)
	{
		if (v.pause || v.s || !core.flag.v)
			v.end = update_proc(&core, vm_func);
		v.s = 0;
		if (core.flag.v)
		{
			print_map(&core, v.speed, wnd, v.pause);
			usleep(1000000 / v.speed);
			input(&v.speed, &v.pause, &v.s);
			werase(wnd);
		}
	}
	print_end(&core, v.speed, wnd, v.pause);
}
