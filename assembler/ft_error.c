/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:17:15 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 10:17:20 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_error1(int i)
{
	if (i == 0)
		perror("\x1B[31mError with the type of file\033[0m");
	else if (i == 1)
		perror("\x1B[31mError opening the file\033[0m");
	else if (i == 2)
		perror("\x1B[31mError: The file is empty\033[0m");
	else if (i == 3)
		perror("\x1B[32mError: Name is too long(> 128).\033[0m");
	else
		perror("\x1B[33mError: Comment is too long(> 2048).\033[0m");
}

void	ft_error2(int i)
{
	if (i == 5)
		write(2, "\x1B[32mNAME\\COMMENT has a duplicate \033[0m", 38);
	else if (i == 6)
		write(2, "\x1B[31mEntered COMMAND without COMMENT/NAME\033[0m", 45);
	else if (i == 7)
		write(2, "\x1B[31mInvalid COMMENT/NAME\033[0m", 29);
	else if (i == 8)
		write(2, "\x1B[34mError due to comment without #/;\033[0m ", 48);
	else if (i == 9)
		write(2, "\x1B[36mNo closing quote\033[0m", 25);
	else
		write(2, "\x1B[31mUnknown command\033[0m", 24);
	write(2, " error at line: ", 16);
	ft_putnbr_fd(g_row, 2);
	ft_putstr("\n");
}

void	ft_error3(int i)
{
	if (i == 11)
		write(2, "\x1B[31mUnknown parameter\033[0m", 26);
	else if (i == 12)
		write(2, "\x1B[32mToo many/few parameter\033[0m", 31);
	else if (i == 13)
		write(2, "\x1B[34mTrouble with coma\033[0m", 26);
	else if (i == 14)
		write(2, "\x1B[33mTrouble with label\033[0m", 27);
	else
		write(2, "\x1B[31mNo such label to dereference\033[0m", 37);
	write(2, " error at line: ", 16);
	ft_putnbr_fd(g_row, 2);
	ft_putstr("\n");
}

int		ft_error(int i)
{
	if (i <= 4)
		ft_error1(i);
	else if (i <= 10)
		ft_error2(i);
	else if (i <= 15)
		ft_error3(i);
	else
		write(2, "\x1B[31mNo new line at the end!\n\033[0m", 33);
	if (i > 1)
		close(g_fd);
	return (-1);
}
