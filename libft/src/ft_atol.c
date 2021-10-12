/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 17:02:42 by jceia             #+#    #+#             */
/*   Updated: 2021/08/27 18:29:19 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	nb;
	int		sgn;

	nb = 0;
	while (ft_isspace(*str))
		str++;
	sgn = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sgn = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nb = 10 * nb + sgn * (*str - '0');
		str++;
	}
	return (nb);
}
