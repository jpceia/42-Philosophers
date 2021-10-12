/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 06:08:23 by jpceia            #+#    #+#             */
/*   Updated: 2021/08/27 18:26:30 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa(unsigned long long nb)
{
	int		index;
	char	*buf;

	if (nb == 0)
		return (ft_straddc(NULL, '0'));
	buf = malloc(21);
	if (!buf)
		return (NULL);
	index = 0;
	while (nb)
	{
		buf[index++] = '0' + nb % 10;
		nb /= 10;
	}
	buf[index] = '\0';
	return (ft_strreverse(buf));
}
