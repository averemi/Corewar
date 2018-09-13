/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 15:39:27 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/06 15:39:29 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "../inc/vm.h"

void	init2(void)
{
	init_pair(11, COLOR_GRAY, COLOR_GRAY);
	init_pair(12, COLOR_WHITE, COLOR_GREEN);
	init_pair(13, COLOR_WHITE, COLOR_BLUE);
	init_pair(14, COLOR_WHITE, COLOR_RED);
	init_pair(15, COLOR_WHITE, COLOR_CYAN);
}

WINDOW	*init(void)
{
	WINDOW	*wnd;

	wnd = initscr();
	cbreak();
	noecho();
	nodelay(wnd, true);
	keypad(wnd, true);
	start_color();
	curs_set(FALSE);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_color(COLOR_GRAY, 400, 400, 400);
	init_pair(10, COLOR_GRAY, COLOR_BLACK);
	init2();
	wbkgd(wnd, COLOR_PAIR(0));
	wrefresh(wnd);
	return (wnd);
}
