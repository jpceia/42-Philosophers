/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:06:27 by jceia             #+#    #+#             */
/*   Updated: 2021/09/10 06:59:06 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	ft_atof_frac(const char *str)
{
	float	x;
	float	pos;

	x = 0;
	pos = 10;
	while (ft_isdigit(*str))
	{
		x += (float)(*str - '0') / pos;
		pos *= 10;
		str++;
	}
	return (x);
}

float	ft_atof(const char *str)
{
	float	x;
	int		sgn;

	x = 0;
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
		x = 10 * x + sgn * (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		x += sgn * ft_atof_frac(str);
	}
	return (x);
}
