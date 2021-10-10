/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:59:06 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 06:48:06 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "philosophers.h"

t_shared	*shared_init(t_shared *shared, int nb_philo)
{
	shared->nb_philo = nb_philo;
	shared->start_time = get_chrono(0);
	shared->stop = false;
	if (!mutex_array_init(shared->forks, nb_philo))
		return (NULL);
	if (pthread_mutex_init(&shared->print_mutex, NULL) < 0)
	{
		perror("Error initializing mutex");
		return (NULL);
	}
	if (pthread_mutex_init(&shared->stop_mutex, NULL) < 0)
	{
		perror("Error initializing mutex");
		return (NULL);
	}
	return (shared);
}

void	shared_clean(t_shared *shared)
{
	pthread_mutex_destroy(&shared->print_mutex);
	pthread_mutex_destroy(&shared->stop_mutex);
	if (shared->forks)
	{
		mutex_array_destroy(shared->forks, shared->nb_philo);
		free(shared->forks);
	}
}

t_data	*data_init(t_data **data, t_shared *shared,
		const t_args *args, int position)
{
	*data = malloc(sizeof(t_data));
	if (!data)
	{
		shared_clean(shared);
		exit(EXIT_FAILURE);
	}
	(*data)->shared = shared;
	(*data)->position = position;
	(*data)->last_meal = 0;
	(*data)->max_meals = args->max_meals;
	(*data)->time_to_die = args->time_to_die;
	(*data)->time_to_eat = args->time_to_eat;
	(*data)->time_to_sleep = args->time_to_sleep;
	return (*data);
}

pthread_t	*threads_init(pthread_t **thread,
		t_shared *shared, t_args *args)
{
	t_data	*data;
	int		index;

	*thread = malloc(sizeof(**thread) * args->nb_philo);
	if (!*thread)
		return (NULL);
	index = 0;
	while (index < args->nb_philo)
	{
		data_init(&data, shared, args, index + 1);
		pthread_create(*thread + index, NULL, routine, data);
		pthread_mutex_lock(&shared->print_mutex);
		printf("Created philo %d\n", index);
		pthread_mutex_unlock(&shared->print_mutex);
		index++;
	}
	return (*thread);
}

void	threads_join(pthread_t *thread, int size)
{
	t_data	*data;
	int		index;

	index = 0;
	while (index < size)
	{
		pthread_join(thread[index++], (void *)data);
		free(data);
		index++;
	}
	free(thread);
}
