/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfil <vfil@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:22:17 by vfil              #+#    #+#             */
/*   Updated: 2018/07/23 14:22:19 by vfil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int		find_winner(t_core *core)
{
	int				i;
	int				id;
	unsigned int	last_cycle;

	i = 0;
	last_cycle = 0;
	id = 0;
	while (i < core->bots_count)
	{
		if (core->bots[i].last_life > last_cycle)
		{
			last_cycle = core->bots[i].last_life;
			id = i;
		}
		i++;
	}
	return (id);
}

void	dump_bots(t_core *core)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < core->bots_count)
	{
		ft_printf("* Player %i, weighing %u bytes, '%s' ('%s')\n", i + 1,
			core->bots[i].size, core->bots[i].name, core->bots[i].comment);
		i++;
	}
}

void	dump_map(t_core *core)
{
	int	i;
	int	j;
	int	line;

	i = 0;
	j = 1;
	ft_printf("0x0000 : ");
	line = 64;
	while (i < MEM_SIZE)
	{
		ft_printf("%02hx ", core->maps.v_map[i]);
		if (!(j % 64) && j < MEM_SIZE)
		{
			ft_printf("\n%#06x : ", line);
			line += 64;
		}
		i++;
		j++;
	}
	ft_printf("\n");
}

void	print_end(t_core *core, unsigned int speed, WINDOW *wnd,
					unsigned int pause)
{
	if (core->flag.v)
	{
		while ((getch()) != '\n')
		{
			print_map(core, speed, wnd, pause);
			print_winner(core);
		}
		werase(wnd);
		delwin(wnd);
		wnd = NULL;
		exit(1);
	}
	else
	{
		dump_bots(core);
		if (core->flag.d)
			dump_map(core);
		else
			dump_winner(core);
	}
}
