/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:26:55 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 05:47:20 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "philosophers.h"

pthread_mutex_t	*mutex_array_init(pthread_mutex_t *arr, int size)
{
	int				index;

	arr = (pthread_mutex_t *)malloc(size * sizeof(*arr));
	if (!arr)
	{
		perror("Error allocating memory");
		return (NULL);
	}
	index = 0;
	while (index < size)
	{
		if (pthread_mutex_init(&arr[index], NULL) < 0)
		{
			perror("Error creating mutex");
			mutex_array_destroy(arr, index);
			return (NULL);
		}
		index++;
	}
	return (arr);
}

void	mutex_array_destroy(pthread_mutex_t *arr, int size)
{
	int	index;

	index = 0;
	while (index < size)
		pthread_mutex_destroy(&arr[index++]);
	free(arr);
}
