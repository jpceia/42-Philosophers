/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:49:22 by jpceia            #+#    #+#             */
/*   Updated: 2021/08/27 17:59:08 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_core(int n, char *buf)
{
	int	index;

	index = 0;
	if (n < 0)
	{
		buf[0] = '-';
		index = 1;
		if (n < -9)
			index += ft_itoa_core(0 - (n / 10), buf + 1);
		buf[index] = '0' - (n % 10);
	}
	else
	{
		if (n > 9)
			index += ft_itoa_core(n / 10, buf);
		buf[index] = '0' + (n % 10);
	}
	buf[index + 1] = 0;
	return (index + 1);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = malloc(12);
	if (!str)
		return (NULL);
	ft_itoa_core(n, str);
	return (str);
}
