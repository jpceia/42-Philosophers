/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:24:19 by jpceia            #+#    #+#             */
/*   Updated: 2021/09/09 02:54:38 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	int		index;
	int		size;

	size = ft_strlen(s);
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	index = 0;
	while (index < size)
	{
		res[index] = f(s[index]);
		index++;
	}
	res[index] = '\0';
	return (res);
}

char	ft_chartolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

char	ft_chartoupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

char	*ft_strlower(char const *s)
{
	return (ft_strmap(s, ft_chartolower));
}

char	*ft_strupper(char const *s)
{
	return (ft_strmap(s, ft_chartoupper));
}
