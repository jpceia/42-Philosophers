/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:17:22 by jceia             #+#    #+#             */
/*   Updated: 2021/08/27 18:27:41 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *str, int n)
{
	char	*res;
	int		size;

	size = 0;
	while (str[size] && size < n)
		size++;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	res[size] = 0;
	while (size--)
		res[size] = str[size];
	return (res);
}
