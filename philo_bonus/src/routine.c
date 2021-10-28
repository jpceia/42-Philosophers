/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:53:03 by jceia             #+#    #+#             */
/*   Updated: 2021/10/28 18:18:08 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_data *data)
{
	while (1)
	{
		if (!try_eat(data))
			break ;
		if (check_if_dead(data))
			break ;
		if (is_satisfied(data))
			break ;
		do_sleep(data);
		if (check_if_dead(data))
			break ;
		do_think(data);
	}
}

t_bool	try_eat(t_data *data)
{
	if (data->nb_philo == 1)
		return (one_philo_die(data));
	semaphore_wait(data->waiter);
	semaphore_wait(data->forks);
	if (check_if_dead(data))
		return (false);
	print_action(data, TAKE_FORK);
	semaphore_wait(data->forks);
	print_action(data, TAKE_FORK);
	semaphore_post(data->waiter);
	if (check_if_dead(data))
		return (false);
	do_eat(data);
	do_release_forks(data);
	return (true);
}

t_bool	one_philo_die(t_data *data)
{
	long	t;

	t = data->last_meal + data->time_to_die - get_chrono(data->start_time);
	if (t > 0)
		usleep(t * 1000);
	do_die(data);
	return (false);
}

t_bool	check_if_dead(t_data *data)
{
	long	t;

	t = get_chrono(data->start_time);
	if (t - data->last_meal > data->time_to_die)
	{
		do_die(data);
		return (true);
	}
	return (false);
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
