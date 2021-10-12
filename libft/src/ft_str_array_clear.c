/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_array_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:29:45 by jceia             #+#    #+#             */
/*   Updated: 2021/09/09 02:54:50 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_str_array_clear(char **str_arr, int len)
{
	int	index;

	index = 0;
	while (index < len)
	{
		free(str_arr[index]);
		index++;
	}
	free(str_arr);
}
