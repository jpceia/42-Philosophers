/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:58:13 by jceia             #+#    #+#             */
/*   Updated: 2021/09/26 02:02:38 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>


long	get_ts_milliseconds(long ts_start)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec / 1000 - ts_start);
}


t_bool	do_wait(t_data *data)
{
	long	ts;

	while (!forks_avail(data))
	{
		ts = get_ts_milliseconds(data->shared->ts_start);
		if (ts - data->last_meal > data->time_to_die)
			return (0);
		pthread_cond_wait(&data->shared->cond, &data->shared->mutex);
	}
	return (1);
}

t_bool	wait_and_eat(t_data *data)
{
	long	ts;

	pthread_mutex_lock(&data->shared->mutex);
	if (do_wait(data) == false);
	{
		data->dead = true;
		data->shared->any_dead = true;
		printf("%lums %d died\n", ts, data->position);
		return (false);
	}
	ts = get_ts_milliseconds(data->shared->ts_start);
	printf("%lums %d is eating\n", ts, data->position);
	forks_lock(data);
	usleep(data->time_to_eat * 1000);
	forks_unlock(data);
	pthread_mutex_unlock(&data->shared->mutex);
	pthread_cond_signal(&data->shared->cond);
	ts = get_ts_milliseconds(data->shared->ts_start);
	data->last_meal = ts;
	if (data->nb_eats > 0)
		data->nb_eats--;
	return (true);
}

void	do_sleep(t_data *data)
{
	long	ts;

	ts = get_ts_milliseconds(data->shared->ts_start);
	printf("%lums %d is sleeping\n", ts, data->position);
	usleep(data->time_to_sleep * 1000);
}

void	*philosopher_routine(void *ptr)
{
	long	ts;
	t_data	*data;

	data = (t_data *)ptr;
	while (!data->shared->any_dead && data->nb_eats > 0)
	{
		ts = get_ts_milliseconds(data->shared->ts_start);
		printf("%lums %d is thinking\n", ts, data->position);
		if (!wait_and_eat(data))
			break ;
		do_sleep(data);
	}
	return ((void *)data);
}
