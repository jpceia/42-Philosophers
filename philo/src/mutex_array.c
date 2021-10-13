/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:26:55 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 21:17:49 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "philosophers.h"

pthread_mutex_t	*mutex_array_init(pthread_mutex_t **arr, int size)
{
	int	index;

	*arr = (pthread_mutex_t *)malloc(size * sizeof(**arr));
	if (!*arr)
	{
		perror(MALLOC_ERR);
		return (NULL);
	}
	index = 0;
	while (index < size)
	{
		if (pthread_mutex_init(&(*arr)[index], NULL) < 0)
		{
			perror(MUTEX_INIT_ERR);
			mutex_array_destroy(*arr, index);
			return (NULL);
		}
		index++;
	}
	return (*arr);
}

void	mutex_array_destroy(pthread_mutex_t *arr, int size)
{
	int	index;

	index = 0;
	while (index < size)
		if (pthread_mutex_destroy(&arr[index++]) != 0)
			perror(MUTEX_DESTROY_ERR);
	free(arr);
}
