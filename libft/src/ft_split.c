/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 05:06:55 by jceia             #+#    #+#             */
/*   Updated: 2021/08/27 18:20:27 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_split_core(char **str_list, char const *s, char c)
{
	int			index;
	int			prev_space;
	char const	*s_cpy;

	prev_space = 1;
	index = 0;
	s_cpy = s;
	while (*s)
	{
		if (*s == c)
		{
			if (!prev_space)
				str_list[index++] = ft_strndup(s_cpy, s - s_cpy);
			prev_space = 1;
		}
		else if (prev_space)
		{
			s_cpy = s;
			prev_space = 0;
		}
		s++;
	}
	if (!prev_space)
		str_list[index++] = ft_strndup(s_cpy, s - s_cpy);
	return (str_list);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**str_list;

	size = ft_strwc(s, c);
	str_list = malloc(sizeof(*str_list) * (size + 1));
	if (str_list == NULL)
		return (NULL);
	str_list[size] = 0;
	str_list = ft_split_core(str_list, s, c);
	return (str_list);
}
