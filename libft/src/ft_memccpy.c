/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:47:05 by jpceia            #+#    #+#             */
/*   Updated: 2021/08/27 17:49:23 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*ptr_dest;
	char	*ptr_src;
	size_t	index;

	ptr_dest = (char *)dest;
	ptr_src = (char *)src;
	index = 0;
	while (index < n)
	{
		ptr_dest[index] = ptr_src[index];
		if (ptr_src[index] == (char)c)
			return (&ptr_dest[index + 1]);
		index++;
	}
	return (NULL);
}
