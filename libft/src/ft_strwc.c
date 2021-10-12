/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:18:51 by jceia             #+#    #+#             */
/*   Updated: 2021/08/27 18:29:38 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Word-Count function
 */
int	ft_strwc(char const *s, char c)
{
	int	count;
	int	prev_space;

	count = 0;
	prev_space = 1;
	while (*s)
	{
		if (*s == c)
			prev_space = 1;
		else if (prev_space)
		{
			count++;
			prev_space = 0;
		}
		s++;
	}
	return (count);
}
