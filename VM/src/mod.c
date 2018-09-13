/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchechai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:07:47 by vchechai          #+#    #+#             */
/*   Updated: 2018/07/24 12:07:48 by vchechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

unsigned int	mod(long long value)
{
	if (value % MEM_SIZE < 0)
		return ((value % MEM_SIZE) + MEM_SIZE);
	else
		return (value % MEM_SIZE);
}
