/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:25:47 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 15:31:31 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

pthread_t	*threads_init(pthread_t **thread,
		t_shared *shared, t_args *args)
{
	t_data	*data;
	int		index;

	*thread = malloc(sizeof(**thread) * args->nb_philo);
	if (!*thread)
	{
		perror(MALLOC_ERR);
		return (NULL);
	}
	index = 0;
	while (index < args->nb_philo)
	{
		data_init(&data, shared, args, index + 1);
		if (pthread_create(*thread + index, NULL, routine, data) != 0)
		{
			perror(THREAD_CREATE_ERR);
			return (NULL);
		}
		index++;
	}
	return (*thread);
}

void	threads_join(pthread_t *thread, int size)
{
	int	index;

	index = 0;
	while (index < size)
		if (pthread_join(thread[index++], NULL))
			perror(THREAD_JOIN_ERR);
	free(thread);
}
