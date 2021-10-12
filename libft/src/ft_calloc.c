/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:42:43 by jpceia            #+#    #+#             */
/*   Updated: 2021/08/27 17:08:47 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	char	*ptr;
	size_t	index;

	ptr = malloc(n * size);
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < n * size)
		ptr[index++] = 0;
	return (ptr);
}
