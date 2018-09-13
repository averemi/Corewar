/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:08:48 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/06 16:08:51 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void			init_maps(t_maps *maps)
{
	int i;

	i = 0;
	maps->v_map = (unsigned char*)malloc(sizeof(unsigned char) *
										(MEM_SIZE + 1));
	maps->c_map = (unsigned char*)malloc(sizeof(unsigned char) *
										(MEM_SIZE + 1));
	maps->c_cycle = (unsigned char*)malloc(sizeof(unsigned char) *
										(MEM_SIZE + 1));
	maps->v_map[MEM_SIZE] = '\0';
	maps->c_map[MEM_SIZE] = '\0';
	maps->c_cycle[MEM_SIZE] = '\0';
	while (i < MEM_SIZE)
	{
		maps->v_map[i] = 0;
		maps->c_map[i] = 0;
		maps->c_cycle[i] = 0;
		i++;
	}
}

void			get_map(t_bot *bots, unsigned int amount, t_maps *maps)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	step;

	step = MEM_SIZE / amount;
	i = 0;
	init_maps(maps);
	while (i < amount)
	{
		j = 0;
		while (j < bots[i].size)
		{
			maps->v_map[j + i * step] = bots[i].code[j];
			maps->c_map[j + i * step] = (unsigned char)(i + 1);
			j++;
		}
		i++;
	}
}
