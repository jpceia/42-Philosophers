/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/17 19:09:37 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

int	do_die(t_data *data)
{
	long	t;

	t = get_chrono(0) - data->shared->start_time;
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
	data->last_meal = get_chrono(0) - data->shared->start_time;
	print_action(data->last_meal, data->position, EAT);
	usleep(data->time_to_eat * 1000);
	data->nb_meals++;
	return (0);
}

int	do_think(t_data *data)
{
	long	t;

	t = get_chrono(0) - data->shared->start_time;
	print_action(t, data->position, THINK);
	usleep(1000 * data->time_to_think);
	return (0);
}

int	do_sleep(t_data *data)
{
	long	t;

	t = get_chrono(0) - data->shared->start_time;
	print_action(t, data->position, SLEEP);
	usleep(data->time_to_sleep * 1000);
	return (0);
}
