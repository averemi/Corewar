/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfil <vfil@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:02:22 by vfil              #+#    #+#             */
/*   Updated: 2018/07/19 12:02:23 by vfil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	print_info(unsigned int speed, t_core *core, unsigned int pause)
{
	attron(COLOR_PAIR(0) | A_BOLD);
	mvprintw(4, 198, "Cycles/seconds limit : %d", speed);
	mvprintw(7, 198, "Cycle : %d", core->cycle);
	if (pause)
		mvprintw(2, 198, "** RUNNING **");
	else
		mvprintw(2, 198, "** PAUSED **");
	mvprintw(9, 198, "Processes : %d", count_proc(core->proc));
	attroff(COLOR_PAIR(0) | A_BOLD);
	print_bots(core);
}

void	print_cycles(t_core *core)
{
	attron(COLOR_PAIR(0) | A_BOLD);
	mvprintw(8 + core->info_row + 2, 198, "CYCLE_TO_DIE : %u",
			core->cycle_to_die);
	mvprintw(8 + core->info_row + 4, 198, "CYCLE_DELTA : %u", CYCLE_DELTA);
	mvprintw(8 + core->info_row + 6, 198, "NBR_LIVE : %u", NBR_LIVE);
	mvprintw(8 + core->info_row + 8, 198, "MAX_CHECKS : %u", MAX_CHECKS);
	attroff(COLOR_PAIR(0) | A_BOLD);
	core->info_row += 9;
}

void	dump_winner(t_core *core)
{
	int id;

	id = find_winner(core);
	ft_printf("Contestant %i, %s, has won !\n", id + 1, core->bots[id].name);
}

void	print_winner(t_core *core)
{
	int id;

	id = find_winner(core);
	attron(COLOR_PAIR(0) | A_BOLD);
	mvprintw(8 + core->info_row + 2, 198, "The winner is : ");
	mvprintw(8 + core->info_row + 4, 198, "Press ENTER to finish");
	attroff(COLOR_PAIR(0) | A_BOLD);
	attron(COLOR_PAIR(id + 1) | A_BOLD);
	mvprintw(8 + core->info_row + 2, 198 + 16, "%s", core->bots[id].name);
	attroff(COLOR_PAIR(id + 1) | A_BOLD);
	core->info_row += 2;
}

void	print_bots(t_core *core)
{
	int	i;

	i = 0;
	core->info_row = 1;
	while (i < core->bots_count)
	{
		attron(COLOR_PAIR(0) | A_BOLD);
		mvprintw(8 + core->info_row + 2, 198, "Player -%d :", i + 1);
		mvprintw(8 + core->info_row + 3, 198, "\tLast live :\t\t\t%u",
					core->bots[i].last_life);
		mvprintw(8 + core->info_row + 4, 198, "\tLives in current period :\t%u",
					core->bots[i].live);
		attroff(COLOR_PAIR(0) | A_BOLD);
		attron(COLOR_PAIR(i + 1) | A_BOLD);
		mvprintw(8 + core->info_row + 2, 198 + 12, "%s", core->bots[i].name);
		attroff(COLOR_PAIR(i + 1) | A_BOLD);
		core->info_row += 4;
		i++;
	}
	print_cycles(core);
}
