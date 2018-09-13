/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:57:22 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/05 14:57:28 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

void			get_vm_func(t_vm_func *func2)
{
	t_vm_func const	func[17] = {
			&vm_live, &vm_ld, &vm_st, &vm_add, &vm_sub, &vm_and, &vm_or, \
			&vm_xor, &vm_zjmp, &vm_ldi, &vm_sti, &vm_fork, &vm_lld, \
			&vm_lldi, &vm_lfork, &vm_aff, &vm_undef
	};
	int				i;

	i = -1;
	while (++i < 17)
		func2[i] = func[i];
}

void			flag(char **argv, t_core *core)
{
	int i;

	i = 0;
	core->flag.v = 0;
	core->flag.d = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "-v") == 0)
			core->flag.v = 1;
		if (ft_strcmp(argv[i], "-d") == 0)
		{
			if (argv[i + 1] && (ft_atoi(argv[i + 1]) > 0
				|| ft_strcmp(argv[i + 1], "0") == 0))
				core->flag.d = ft_atoi(argv[i + 1]);
			else
				ft_exit("Can't read source file -d\n");
		}
		i++;
	}
}

unsigned int	count_bots(int argc, char **argv)
{
	int				i;
	unsigned int	count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (ft_strstr(argv[i], ".cor"))
			count++;
		i++;
	}
	if (count > 4)
		return (0);
	return (count);
}

int				main(int argc, char **argv)
{
	t_core			core;
	t_vm_func		*vm_func;

	vm_func = (t_vm_func*)malloc(sizeof(t_vm_func) * 17);
	get_vm_func(vm_func);
	core.bots_count = count_bots(argc, argv);
	core.bots = get_bots(argc, argv, core.bots_count);
	get_map(core.bots, core.bots_count, &core.maps);
	init_proceses(core.bots, core.bots_count, &core);
	flag(argv, &core);
	core.cycle_to_die = CYCLE_TO_DIE;
	core.checks = 0;
	core.decycle = 0;
	core.cycle = 0;
	core.new_reset = core.cycle_to_die;
	run(core, vm_func);
}
