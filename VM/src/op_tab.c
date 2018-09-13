/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfil <vfil@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 17:16:50 by vfil              #+#    #+#             */
/*   Updated: 2018/07/26 17:16:59 by vfil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/op.h"

t_op	g_op_tab[17] =
{
	{0x01, 1, {T_DIR}, 10, 4},
	{0x02, 2, {T_DIR | T_IND, T_REG}, 5, 4},
	{0x03, 2, {T_REG, T_IND | T_REG}, 5, 4},
	{0x04, 3, {T_REG, T_REG, T_REG}, 10, 4},
	{0x05, 3, {T_REG, T_REG, T_REG}, 10, 4},
	{0x06, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 4},
	{0x07, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 4},
	{0x08, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 4},
	{0x09, 1, {T_DIR}, 20, 2},
	{0x0a, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 2},
	{0x0b, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 2},
	{0x0c, 1, {T_DIR}, 800, 2},
	{0x0d, 2, {T_DIR | T_IND, T_REG}, 10, 4},
	{0x0e, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 2},
	{0x0f, 1, {T_DIR}, 1000, 2},
	{0x10, 1, {T_REG}, 2, 4},
	{0, 0, {0}, 1, 0}
};
