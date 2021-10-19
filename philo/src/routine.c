/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:05 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 16:03:09 by jceia            ###   ########.fr       */
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
		if (data->shared->stop)
			break ;
		if (do_think(data) < 0)
			break ;
	}
	free(data);
	return (NULL);
}

void	one_philo_die(t_data *data)
{
	long	t;

	t = get_chrono(data->shared->start_time);
	usleep((data->last_meal + data->time_to_die - t) * 1000);
	do_die(data);
}

t_bool	check_if_dead(t_data *data)
{
	long	t;

	t = get_chrono(data->shared->start_time);
	if (t - data->last_meal > data->time_to_die)
	{
		do_die(data);
		return (true);
	}
	return (false);
}

int	try_eat(t_data *data)
{
	t_shared	*shared;

	shared = data->shared;
	if (shared->nb_philo == 1)
	{
		one_philo_die(data);
		return (-1);
	}
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
	long	t;

	index = 0;
	while (index < args->nb_philo)
	{
		t = get_chrono(0) - shared->start_time;
		if (shared->last_meal[index] + args->time_to_die < t)
		{
			t = shared->last_meal[index] + args->time_to_die;
			pthread_mutex_lock(&shared->stop_mutex);
			if (!shared->stop)
			{
				shared->stop = true;
				print_action(t, index + 1, DEAD);
			}
			pthread_mutex_unlock(&shared->stop_mutex);
			return (true);
		}
		index++;
	}
	usleep((int)(1000 * args->time_to_check));
	return (false);
}
