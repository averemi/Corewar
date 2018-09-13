/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 11:54:57 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/14 11:54:57 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm.h"

int			ft_check_under(int num, int op)
{
	if (num != 1 && (op == 1 || op == 9 || op == 12 || op == 15 || op == 16))
		return (-1);
	else if (num != 2 && (op == 2 || op == 3 || op == 13))
		return (-1);
	else if (num != 3 && ((op >= 4 && op <= 8) || op == 10\
		|| op == 11 || op == 14))
		return (-1);
	else
		return (0);
}

t_parser	*ft_new_par(void)
{
	t_parser *new;

	new = (t_parser*)malloc(sizeof(t_parser));
	ft_bzero(new, sizeof(t_parser));
	new->type = 0;
	new->codage = 0;
	new->label = NULL;
	new->args = NULL;
	new->size = 0;
	return (new);
}

t_label		*ft_new_label(t_label **head, char *s, int len)
{
	t_label *lst;

	lst = *head;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = (t_label*)malloc(sizeof(t_label));
		lst = lst->next;
		lst->name = ft_strncpy(ft_strnew(len), s, len);
		lst->next = NULL;
		return (lst);
	}
	else
	{
		lst = (t_label*)malloc(sizeof(t_label));
		lst->name = ft_strncpy(ft_strnew(len), s, len);
		lst->next = NULL;
		*head = lst;
		return (lst);
	}
}

static void	ft_set_arg_size(t_args *lst, int type)
{
	if (type == 1)
		lst->arg_size = 1;
	else if (type == 3 || type == 4)
		lst->arg_size = 4;
	else
		lst->arg_size = 2;
}

t_args		*ft_new_arg(t_args **head, char *val, int value, int type)
{
	t_args *lst;

	lst = *head;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = (t_args*)malloc(sizeof(t_args));
		lst = lst->next;
	}
	else
	{
		lst = (t_args*)malloc(sizeof(t_args));
		*head = lst;
	}
	ft_set_arg_size(lst, type);
	lst->type_arg = type > 0 ? type : type * -1;
	if (val)
		lst->val = ft_strncpy(ft_strnew(ft_strlen(val)), val, ft_strlen(val));
	else
		lst->val = NULL;
	lst->value = value;
	lst->next = NULL;
	return (lst);
}
