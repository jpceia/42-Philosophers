/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:05 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 16:44:37 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		do_sleep(data);
		if (data->shared->stop)
			break ;
		do_think(data);
	}
	free(data);
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
	int			index[2];

	shared = data->shared;
	if (shared->nb_philo == 1)
		return (one_philo_die(data));
	forks_indexes(index, data->position, shared->nb_philo);
	pthread_mutex_lock(&shared->forks[index[0]]);
	if (check_if_dead(data))
		return (false);
	print_action(data, TAKE_FORK);
	pthread_mutex_lock(&shared->forks[index[1]]);
	if (shared->stop)
		return (false);
	if (check_if_dead(data))
	{
		forks_release(index, shared->forks);
		return (false);
	}
	do_eat(data);
	forks_release(index, shared->forks);
	return (true);
}
