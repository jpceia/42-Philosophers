/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:59:06 by jceia             #+#    #+#             */
/*   Updated: 2021/10/17 16:13:54 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "philosophers.h"
#include "libft.h"

t_shared	*shared_init(t_shared *shared, int nb_philo)
{
	memset(shared, 0, sizeof(*shared));
	shared->nb_philo = nb_philo;
	shared->start_time = get_chrono(0);
	shared->stop = false;
	if (!mutex_array_init(&shared->forks, nb_philo))
		return (NULL);
	if (pthread_mutex_init(&shared->stop_mutex, NULL) < 0)
	{
		perror(MUTEX_INIT_ERR);
		return (NULL);
	}
	return (shared);
}

void	shared_clean(t_shared *shared)
{
	pthread_mutex_destroy(&shared->stop_mutex);
	if (shared->forks)
		mutex_array_destroy(shared->forks, shared->nb_philo);
}

t_data	*data_init(t_data **data, t_shared *shared,
		const t_args *args, int position)
{
	int	idx[2];

	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		shared_clean(shared);
		perror(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
	memset(*data, 0, sizeof(**data));
	(*data)->shared = shared;
	(*data)->position = position;
	(*data)->max_meals = args->max_meals;
	(*data)->time_to_die = args->time_to_die;
	(*data)->time_to_eat = args->time_to_eat;
	(*data)->time_to_sleep = args->time_to_sleep;
	forks_indexes(idx, position, shared->nb_philo);
	(*data)->fork1 = shared->forks + idx[0];
	(*data)->fork2 = shared->forks + idx[1];
	return (*data);
}

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
