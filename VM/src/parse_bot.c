/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfil <vfil@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 16:30:56 by vfil              #+#    #+#             */
/*   Updated: 2018/07/02 16:31:03 by vfil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	get_name(int fd, t_bot *bot)
{
	unsigned int	tmp;

	if ((read(fd, bot->name, PROG_NAME_LENGTH)) < PROG_NAME_LENGTH)
		ft_exit("Incorrect name length");
	bot->name[PROG_NAME_LENGTH] = '\0';
	tmp = 1;
	if ((read(fd, &tmp, 4)) < 4 || tmp != 0)
		ft_exit("Incorrect binary format");
}

void	get_bot_size(int fd, t_bot *bot)
{
	unsigned char	buf[4];

	if ((read(fd, buf, 4)) < 4)
		ft_exit("Incorrect binary format");
	bot->size = swap_4bits(buf);
	if (bot->size <= 0 || bot->size > CHAMP_MAX_SIZE)
		ft_exit("Incorrect binary format");
}

void	get_comment(int fd, t_bot *bot)
{
	unsigned int	tmp;

	if ((read(fd, bot->comment, COMMENT_LENGTH)) < COMMENT_LENGTH)
		ft_exit("Can't read from file");
	bot->comment[COMMENT_LENGTH] = '\0';
	tmp = 1;
	if ((read(fd, &tmp, 4)) < 4 || tmp != 0)
		ft_exit("Incorrect binary format");
}

void	get_bot_code(int fd, t_bot *bot)
{
	unsigned char	buf[2];
	int				ret;
	unsigned int	i;
	short			two_bytes;

	i = 0;
	while ((ret = read(fd, buf, 2)) == 2)
	{
		two_bytes = swap_2bits(buf);
		bot->code[i] = (unsigned char)(two_bytes >> 8);
		bot->code[i + 1] = (unsigned char)two_bytes;
		i += 2;
		if (i >= CHAMP_MAX_SIZE)
			ft_exit("Error: File champs/42.cor has too large a code");
	}
	if (ret == 1)
		bot->code[i] = buf[0];
	if (ret < 0)
		ft_exit("Can't read from file");
	bot->code[bot->size] = '\0';
}

t_bot	parse_bot(char *bot_name)
{
	t_bot			bot;
	int				fd;
	unsigned char	buf[4];

	if ((fd = open(bot_name, O_RDONLY)) <= 0)
		ft_exit("Can't open file");
	if ((read(fd, buf, 4)) < 4)
		ft_exit("Can't read from file");
	if (swap_4bits(buf) != COREWAR_EXEC_MAGIC)
		exit(0);
	get_name(fd, &bot);
	get_bot_size(fd, &bot);
	get_comment(fd, &bot);
	get_bot_code(fd, &bot);
	bot.last_life = 0;
	bot.live = 0;
	close(fd);
	return (bot);
}
