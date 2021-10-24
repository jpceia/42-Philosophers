/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 16:00:29 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

int	do_die(t_data *data)
{
	long	t;

	t = timestamp();
	if (data->shared->stop)
		return (0);
	pthread_mutex_lock(&data->shared->stop_mutex);
	data->shared->stop = true;
	print_action(t, data->position, DEAD);
	pthread_mutex_unlock(&data->shared->stop_mutex);
	return (0);
}

int	do_eat(t_data *data)
{
	if (data->shared->stop)
	{
		do_release_forks(data);
		return (-1);
	}
	data->last_meal = timestamp();
	pthread_mutex_lock(&data->shared->last_meal_mutex);
	data->shared->last_meal[data->position - 1] = data->last_meal;
	pthread_mutex_unlock(&data->shared->last_meal_mutex);
	print_action(data->last_meal, data->position, EAT);
	usleep(data->time_to_eat * 1000);
	data->nb_meals++;
	if (data->meals_must_eat > 0 && data->nb_meals == data->meals_must_eat)
	{
		pthread_mutex_lock(&data->shared->satisfied_mutex);
		data->shared->nb_satisfied++;
		if (data->shared->nb_satisfied == data->shared->nb_philo)
		{
			pthread_mutex_lock(&data->shared->stop_mutex);
			data->shared->stop = true;
			pthread_mutex_unlock(&data->shared->stop_mutex);
		}
		pthread_mutex_unlock(&data->shared->satisfied_mutex);
	}
	return (0);
}

int	do_think(t_data *data)
{
	long	t;

	t = timestamp();
	print_action(t, data->position, THINK);
	usleep((int)(1000 * data->time_to_think));
	return (0);
}

int	do_sleep(t_data *data)
{
	long	t;

	t = timestamp();
	print_action(t, data->position, SLEEP);
	usleep(data->time_to_sleep * 1000);
	return (0);
}
