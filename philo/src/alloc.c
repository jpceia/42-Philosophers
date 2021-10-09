/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:59:06 by jceia             #+#    #+#             */
/*   Updated: 2021/09/26 02:16:35 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "philosophers.h"


void	shared_init(t_shared *shared, int nb_philosophers)
{
	shared->nb_philosophers = nb_philosophers;
	shared->ts_start = get_ts_milliseconds(0);
	shared->any_dead = false;
	pthread_cond_init(&shared->cond, NULL);
	pthread_mutex_init(&shared->mutex, NULL);
	shared->forks = malloc(sizeof(t_bool) * nb_philosophers);
	memset(shared->forks, 0, sizeof(t_bool) * nb_philosophers);
}

void	shared_clean(t_shared *shared)
{
	pthread_cond_destroy(&shared->cond);
	pthread_mutex_destroy(&shared->mutex);
	if (shared->forks)
		free(shared->forks);
}

void	data_init(t_data **data, t_shared *shared,
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
	(*data)->dead = false;
	(*data)->last_meal = 0;
	(*data)->nb_eats = args->nb_eats;
	(*data)->time_to_die = args->time_to_die;
	(*data)->time_to_eat = args->time_to_eat;
	(*data)->time_to_sleep = args->time_to_sleep;
}

void	args_init(t_args *args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		exit(EXIT_SUCCESS);
	}
	args->nb_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	args->nb_eats = -1;
	if (argc == 6)
		args->nb_eats = atoi(argv[5]);
}

void	threads_init(pthread_t **t, t_data *data, t_shared *shared, t_args *args)
{
	int	index;

	index = 0;
	*t = malloc(sizeof(**t) * args->nb_philosophers);
	if (!t)
	{
		free(data);
		shared_clean(shared);
		exit(EXIT_FAILURE);
	}
	while (index < args->nb_philosophers)
	{
		data_init(&data, shared, args, index + 1);
		pthread_create(*t + index, NULL, &philosopher_routine, data);
		index++;
	}
}
