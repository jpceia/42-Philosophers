/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:59:06 by jceia             #+#    #+#             */
/*   Updated: 2022/03/31 18:29:49 by jpceia           ###   ########.fr       */
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
	shared->stop = false;
	shared->last_meal = ft_calloc(nb_philo, sizeof(*shared->last_meal));
	if (!shared->last_meal)
	{
		perror(MALLOC_ERR);
		return (NULL);
	}
	if (!mutex_array_init(&shared->forks, nb_philo))
		return (NULL);
	pthread_mutex_init(&shared->stop_mutex, NULL);
	pthread_mutex_init(&shared->print_mutex, NULL);
	pthread_mutex_init(&shared->satisfied_mutex, NULL);
	pthread_mutex_init(&shared->last_meal_mutex, NULL);
	return (shared);
}

void	shared_clean(t_shared *shared)
{
	pthread_mutex_destroy(&shared->stop_mutex);
	pthread_mutex_destroy(&shared->print_mutex);
	pthread_mutex_destroy(&shared->satisfied_mutex);
	pthread_mutex_destroy(&shared->last_meal_mutex);
	if (shared->forks)
		mutex_array_destroy(shared->forks, shared->nb_philo);
	if (shared->last_meal)
		free(shared->last_meal);
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
	(*data)->meals_must_eat = args->meals_must_eat;
	(*data)->time_to_die = args->time_to_die;
	(*data)->time_to_eat = args->time_to_eat;
	(*data)->time_to_sleep = args->time_to_sleep;
	(*data)->time_to_think = args->time_to_think;
	forks_indexes(idx, position, shared->nb_philo);
	(*data)->fork1 = shared->forks + idx[0];
	(*data)->fork2 = shared->forks + idx[1];
	return (*data);
}
