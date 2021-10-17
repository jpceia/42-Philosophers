/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:05 by jceia             #+#    #+#             */
/*   Updated: 2021/10/17 17:35:35 by jceia            ###   ########.fr       */
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
		if (!try_eat(data))
			break ;
		if (data->shared->stop)
			break ;
		if (is_satisfied(data))
			break ;
		if (do_sleep(data) < 0)
			break ;
		if (data->shared->stop)
			break ;
		if (do_think(data) < 0)
			break;
	}
	free(data);
	return (NULL);
}

t_bool	is_satisfied(t_data *data)
{
	if (data->max_meals > 0 && data->nb_meals == data->max_meals)
	{
		print_action(data, SATISFIED);
		return (true);
	}
	return (false);
}

t_bool	one_philo_die(t_data *data)
{
	long	t;

	t = get_chrono(data->shared->start_time);
	usleep((data->last_meal + data->time_to_die - t) * 1000);
	do_die(data);
	return (false);
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

t_bool	try_eat(t_data *data)
{
	t_shared	*shared;

	shared = data->shared;
	if (shared->nb_philo == 1)
		return (one_philo_die(data));
	if (pthread_mutex_lock(data->fork1) != 0)
	{
		perror(MUTEX_LOCK_ERR);
		return (false);
	}
	if (shared->stop || check_if_dead(data))
	{
		pthread_mutex_unlock(data->fork1);
		return (false);
	}
	print_action(data, TAKE_FORK);
	if (pthread_mutex_lock(data->fork2) != 0)
	{
		perror(MUTEX_LOCK_ERR);
		return (false);
	}
	if (shared->stop || check_if_dead(data))
	{
		do_release_forks(data);
		return (false);
	}
	if (do_eat(data) < 0)
		return (false);
	if (do_release_forks(data) < 0)
		return (false);
	return (true);
}