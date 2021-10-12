/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:44:47 by jpceia            #+#    #+#             */
/*   Updated: 2021/09/09 03:48:11 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*l;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	l = *lst;
	while (l->next)
		l = l->next;
	l->next = node;
}
