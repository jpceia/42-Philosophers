/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 06:30:12 by jpceia            #+#    #+#             */
/*   Updated: 2021/08/27 18:25:54 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa_base(unsigned long long nb, const char *base)
{
	int		base_size;
	int		index;
	char	*buf;

	if (nb == 0)
		return (ft_straddc(NULL, base[0]));
	base_size = ft_strlen(base);
	if (base_size <= 1)
		return (NULL);
	buf = malloc(64);
	if (!buf)
		return (NULL);
	index = 0;
	while (nb)
	{
		buf[index++] = base[nb % base_size];
		nb /= base_size;
	}
	buf[index] = '\0';
	return (ft_strreverse(buf));
}
