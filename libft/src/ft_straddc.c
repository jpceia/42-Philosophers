/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 15:58:21 by jceia             #+#    #+#             */
/*   Updated: 2021/08/27 18:28:24 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddc(char *s, char c)
{
	char	*s_new;
	int		len;

	if (s)
		len = ft_strlen(s);
	else
		len = 0;
	s_new = malloc(len + 2);
	if (!s_new)
		return (NULL);
	if (s)
	{
		ft_memcpy(s_new, s, len);
		free(s);
	}
	s_new[len] = c;
	s_new[len + 1] = 0;
	return (s_new);
}
