/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 06:08:23 by jpceia            #+#    #+#             */
/*   Updated: 2021/08/27 18:13:31 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa(long long nb)
{
	int		index;
	int		sign;
	char	*buf;

	if (nb == 0)
		return (ft_straddc(NULL, '0'));
	buf = malloc(21);
	if (!buf)
		return (NULL);
	sign = (nb < 0);
	if (!sign)
		nb = -nb;
	index = 0;
	while (nb)
	{
		buf[index++] = '0' - nb % 10;
		nb /= 10;
	}
	if (sign)
		buf[index++] = '-';
	buf[index] = '\0';
	return (ft_strreverse(buf));
}
