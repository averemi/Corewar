/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 16:51:26 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/03 16:51:28 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int				ft_check_args(int argc, char **argv)
{
	int	i;

	i = ft_strlen(argv[argc - 1]);
	if (argc == 1)
	{
		write(1, "Usage: ./asm <sourcefile.s>\n", 28);
		return (-1);
	}
	else
	{
		if (i < 2 || (argv[argc - 1][i - 2] != '.' &&\
			argv[argc - 1][i - 1] != 's'))
			return (ft_error(0));
	}
	return (0);
}

static int				ft_create_cor(char *path)
{
	char	*tmp;

	tmp = ft_strcpy(ft_strnew(ft_strlen(path) + 2), path);
	ft_strcpy(ft_strstr(tmp, ".s"), ".cor");
	if ((g_fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0777)) < 0)
		return (ft_error(1));
	ft_printf("Writing output program to %s\n", tmp);
	free(tmp);
	tmp = NULL;
	return (0);
}

static int				ft_open_file(char *name)
{
	if ((g_fd = open(name, O_RDWR)) == -1)
		return (ft_error(1));
	else if (!g_fd)
		return (ft_error(2));
	return (0);
}

int						main(int argc, char **argv)
{
	t_parser	*par;
	char		*line;

	g_last_line = 0;
	g_row = 0;
	g_file = 0;
	if (ft_check_args(argc, argv))
		return (1);
	if (ft_open_file(argv[argc - 1]))
		return (1);
	par = ft_new_par();
	if (ft_get_info(par, &line) || (g_file < 3 && ft_error(2)))
		return (1);
	ft_count_codage(par);
	ft_get_param_size(par);
	if (ft_count_labels(par))
		return (1);
	if (ft_create_cor(argv[argc - 1]))
		return (-1);
	ft_translation(g_fd, par);
	return (0);
}
