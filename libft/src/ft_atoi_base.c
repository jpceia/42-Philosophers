/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:09:12 by jceia             #+#    #+#             */
/*   Updated: 2021/09/10 08:47:48 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chartoi_base(char c, char *base)
{
	int	index;

	index = 0;
	while (base[index])
	{
		if (c == base[index])
			return (index);
		index++;
	}
	return (-1);
}

/*
 * Calculates the base size and checks if it is valid
 */
static int	ft_base_size(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || ft_isspace(base[i]))
			return (0);
		i++;
	}
	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_atoi_base(const char *str, char *base)
{
	int	index;
	int	base_size;
	int	sgn;
	int	nb;

	base_size = ft_base_size(base);
	if (base_size < 2)
		return (0);
	while (ft_isspace(*str))
		str++;
	sgn = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sgn = -1;
	nb = 0;
	while (ft_contains(*str, base))
	{
		index = ft_chartoi_base(*str++, base);
		if (index < 0)
			break ;
		nb = nb * base_size + sgn * index;
	}
	return (nb);
}
