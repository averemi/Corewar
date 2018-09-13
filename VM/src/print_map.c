/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:05:56 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/09 13:05:59 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	check_color(t_core *core, int position, t_proc *proc)
{
	attroff(A_BOLD);
	while (proc)
	{
		if (proc->pc == position)
		{
			attron(COLOR_PAIR(core->maps.c_map[position] + 5));
			return ;
		}
		proc = proc->next;
	}
	if (core->maps.c_cycle[position] > 0)
		attron(COLOR_PAIR(core->maps.c_map[position]) | A_BOLD);
	else if (core->maps.c_map[position] == 0)
		attron(COLOR_PAIR(10) | A_BOLD);
	else
		attron(COLOR_PAIR(core->maps.c_map[position]));
}

void	print_border(WINDOW *wnd)
{
	wattron(wnd, COLOR_PAIR(11));
	wborder(wnd, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(wnd, COLOR_PAIR(11));
}

void	print_map(t_core *core, unsigned int speed, WINDOW *wnd,
					unsigned int pause)
{
	int i;
	int y;
	int x;

	y = 1;
	x = 1;
	i = 0;
	while (i < MEM_SIZE)
	{
		check_color(core, i, core->proc);
		mvprintw(y, x * 3, "%02hx", core->maps.v_map[i]);
		attron(COLOR_PAIR(10) | A_BOLD);
		if (x == 64)
		{
			y++;
			x = 0;
		}
		x++;
		i++;
	}
	attroff(COLOR_PAIR(10) | A_BOLD);
	print_border(wnd);
	print_info(speed, core, pause);
	refresh();
}
