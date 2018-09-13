/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:12:57 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/13 11:12:59 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

unsigned char	*get_codage(unsigned char value)
{
	unsigned char	*codage;

	codage = (unsigned char *)malloc(sizeof(unsigned char) * 4);
	codage[0] = value >> 6;
	codage[1] = value << 2;
	codage[1] = codage[1] >> 6;
	codage[2] = value << 4;
	codage[2] = codage[2] >> 6;
	codage[3] = '\0';
	return (codage);
}

char			*get_types(char value)
{
	char	all_types[3];
	char	*res;
	int		i;

	i = 0;
	res = (char*)malloc(sizeof(char) * 4);
	all_types[0] = T_IND;
	all_types[1] = T_DIR;
	all_types[2] = T_REG;
	while (value > 0 && i < 3)
	{
		if (value >= all_types[i])
		{
			if (all_types[i] == T_IND)
				res[i] = 3;
			else
				res[i] = all_types[i];
			value -= all_types[i];
		}
		else
			res[i] = 0;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char			check_codage(t_core *core, t_proc *curr_proc)
{
	unsigned char	*cdg;
	int				i;
	t_op			tab;
	char			*types;

	i = 0;
	tab = g_op_tab[cmd_id(curr_proc->code)];
	cdg = get_codage(core->maps.v_map[MEM(curr_proc->pc + 1)]);
	while (i < tab.nb_params)
	{
		types = get_types(tab.type[i]);
		if (cdg[i] == 0 || (cdg[i] != types[0] && cdg[i] != types[1]
							&& cdg[i] != types[2]))
		{
			free(cdg);
			free(types);
			return (0);
		}
		free(types);
		i++;
	}
	free(cdg);
	return (1);
}

unsigned int	determ_arg(unsigned char codage, t_core *core, t_proc *proc,
							unsigned char *skip)
{
	unsigned int	res;
	unsigned int	tind2;

	res = 0;
	if (codage == DIR_CODE)
	{
		if (g_op_tab[cmd_id(proc->code)].label == 2)
			res = get_tdir(2, core, proc->pc + *skip);
		else
			res = get_tdir(4, core, proc->pc + *skip);
		*skip += g_op_tab[cmd_id(proc->code)].label - 1;
	}
	else if (codage == IND_CODE)
	{
		tind2 = get_tdir(IND_SIZE, core, proc->pc + *skip);
		*skip += 1;
		res = get_tdir(DIR_SIZE, core, mod(proc->pc + (short)tind2 % IDX_MOD));
	}
	return (res);
}

unsigned int	*get_args(t_core *core, t_proc *proc, char t_reg)
{
	unsigned int	*arg;
	unsigned char	*codage;
	int				i;
	unsigned char	skip;

	arg = (unsigned int*)malloc(sizeof(unsigned int) * 3);
	codage = get_codage(core->maps.v_map[MEM(proc->pc + 1)]);
	skip = 2;
	i = 0;
	while (i < 3)
	{
		if (codage[i] == REG_CODE && t_reg == T_REG_VALUE)
			arg[i] = proc->reg[REG(core->maps.v_map[MEM(proc->pc + skip)])];
		else if (codage[i] == REG_CODE && t_reg == T_REG_NUMBER)
			arg[i] = REG(core->maps.v_map[MEM(proc->pc + skip)]);
		else
			arg[i] = determ_arg(codage[i], core, proc, &skip);
		skip++;
		i++;
	}
	free(codage);
	return (arg);
}
