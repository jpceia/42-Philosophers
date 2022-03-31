/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:05 by jceia             #+#    #+#             */
/*   Updated: 2022/03/31 18:39:54 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	*routine(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		if (try_eat(data) < 0)
			break ;
		if (data->shared->stop)
			break ;
		if (do_sleep(data) < 0)
			break ;
		pthread_mutex_lock(&data->shared->stop_mutex);
		if (data->shared->stop)
			break ;
		pthread_mutex_unlock(&data->shared->stop_mutex);
		if (do_think(data) < 0)
			break ;
	}
	free(data);
	return (NULL);
}

int	try_eat(t_data *data)
{
	t_shared	*shared;

	shared = data->shared;
	if (shared->nb_philo == 1)
		return (-1);
	if (do_take_forks(data) < 0)
		return (-1);
	if (do_eat(data) < 0)
		return (-1);
	if (do_release_forks(data) < 0)
		return (-1);
	return (0);
}

t_bool	check_philosophers_dead(t_shared *shared, t_args *args)
{
	int		index;
	int		is_dead;

	index = 0;
	is_dead = 0;
	while (index < args->nb_philo)
	{
		pthread_mutex_lock(&shared->last_meal_mutex);
		is_dead = shared->last_meal[index] + args->time_to_die < timestamp();
		pthread_mutex_unlock(&shared->last_meal_mutex);
		if (is_dead)
		{
			pthread_mutex_lock(&shared->stop_mutex);
			if (!shared->stop)
			{
				shared->stop = true;
				print_action(index + 1, DEAD, &shared->print_mutex);
			}
			pthread_mutex_unlock(&shared->stop_mutex);
			return (true);
		}
		index++;
	}
	return (false);
}
