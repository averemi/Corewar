/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:13:40 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 12:13:44 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **split)
{
	int i;

	i = -1;
	while (split[++i])
	{
		free(split[i]);
		split[i] = NULL;
	}
	free(split);
	split = NULL;
}
