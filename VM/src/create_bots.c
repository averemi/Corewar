/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 19:46:29 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/24 19:46:31 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int		*parse_flags(t_bot **bots, char **argv, int argc,
							int size)
{
	int	arg;
	int	i;
	int	count;
	int	*arr;

	i = 0;
	count = 0;
	arr = (int*)malloc(sizeof(int) * size);
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-n") && argv[i + 1] && argv[i + 2])
		{
			arg = ft_atoi(argv[i + 1]);
			if (arg > 0 && (arg - 1) < size && ft_strstr(argv[i + 2], ".cor"))
			{
				(*bots)[arg - 1] = parse_bot(argv[i + 2]);
				(*bots)[arg - 1].id = arg - 1;
				arr[count++] = arg - 1;
				i += 2;
			}
		}
		else if (ft_strstr(argv[i], ".cor"))
			arr[count++] = -1;
	}
	return (arr);
}

int		check_num(int i, int *nbots, int count)
{
	int k;

	k = 0;
	while (k < count)
	{
		if (nbots[k] == i)
			return (1);
		k++;
	}
	return (0);
}

char	check_bot(char **argv, int i, int size)
{
	int arg;

	if (argv[i - 1] && argv[i - 2])
	{
		arg = ft_atoi(argv[i - 1]);
		if (arg > 0 && (arg - 1) < size && !ft_strcmp(argv[i - 2], "-n"))
			return (1);
	}
	return (0);
}

t_bot	*get_bots(int argc, char **argv, unsigned int size)
{
	t_bot			*bots;
	int				i;
	unsigned int	count;
	int				*nbots;

	count = 0;
	i = 0;
	if (size > MAX_PLAYERS || size <= 0)
		ft_exit("wrong bots");
	bots = (t_bot *)malloc(sizeof(t_bot) * size);
	nbots = parse_flags(&bots, argv, argc, size);
	while (++i < argc)
	{
		while (check_num(count, nbots, size))
			count++;
		if (ft_strstr(argv[i], ".cor") && !check_bot(argv, i, size))
		{
			bots[count] = parse_bot(argv[i]);
			bots[count].id = count;
			count++;
		}
	}
	free(nbots);
	return (bots);
}
