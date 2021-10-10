/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 06:21:08 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

void	do_stop(t_shared *shared)
{
	pthread_mutex_lock(&shared->stop_mutex);
	shared->stop = true;
	pthread_mutex_unlock(&shared->stop_mutex);
}

void	do_die(t_data *data)
{
	print_action(data, DEAD);
	do_stop(data->shared);
}

t_bool	try_eat(t_data *data)
{
	int		left_fork_index;
	int		right_fork_index;
	long	t;

	left_fork_index = data->position % data->shared->nb_philo;
	right_fork_index = (data->position + 1) % data->shared->nb_philo;
	pthread_mutex_lock(&data->shared->forks[left_fork_index]);
	pthread_mutex_lock(&data->shared->forks[right_fork_index]);
	t = get_chrono(data->shared->start_time);
	if (data->shared->stop)
		return (false);
	if (t - data->last_meal > data->time_to_die)
	{
		do_die(data);
		return (false);
	}
	print_action(data, EAT);
	usleep(data->time_to_sleep * 1000);
	data->last_meal = get_chrono(data->shared->start_time);
	data->nb_meals++;
	pthread_mutex_unlock(&data->shared->forks[left_fork_index]);
	pthread_mutex_unlock(&data->shared->forks[right_fork_index]);
	return (true);
}

void	do_think(t_data *data)
{
	print_action(data, THINK);
}

void	do_sleep(t_data *data)
{
	print_action(data, SLEEP);
	usleep(data->time_to_sleep * 1000);
}
