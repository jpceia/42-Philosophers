/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:53:03 by jceia             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/28 17:02:49 by jceia            ###   ########.fr       */
=======
/*   Updated: 2021/10/29 04:02:10 by jceia            ###   ########.fr       */
>>>>>>> ffd2f5a7ee5e22c845bd3e2fd393f23e58d53e3a
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_data *data)
{
	while (1)
	{
		if (!try_eat(data))
			break ;
		if (data->stop)
			break ;
		do_sleep(data);
		if (data->stop)
			break ;
		do_think(data);
	}
}

t_bool	release_exit(t_data *data, int n_forks, int n_waiters)
{
	while (n_forks--)
		semaphore_post(data->forks);
	while (n_waiters--)
		semaphore_post(data->waiter);
	return (false);
}

t_bool	try_eat(t_data *data)
{
	if (data->nb_philo == 1)
		return (one_philo_die(data));
	semaphore_wait(data->waiter);
<<<<<<< HEAD
	semaphore_wait(data->forks);
	if (check_if_dead(data))
		return (false);
	print_action(data, TAKE_FORK);
	semaphore_wait(data->forks);
	print_action(data, TAKE_FORK);
	semaphore_post(data->waiter);
	if (check_if_dead(data))
		return (false);
=======
	if (data->stop)
		return (release_exit(data, 0, 1));
	semaphore_wait(data->forks);
	if (data->stop)
		return (release_exit(data, 1, 1));
	print_action(data, TAKE_FORK);
	semaphore_wait(data->forks);
	if (data->stop)
		return (release_exit(data, 2, 1));
	print_action(data, TAKE_FORK);
	semaphore_post(data->waiter);
	if (data->stop)
		return (release_exit(data, 2, 0));
>>>>>>> ffd2f5a7ee5e22c845bd3e2fd393f23e58d53e3a
	do_eat(data);
	do_release_forks(data);
	return (true);
}

t_bool	one_philo_die(t_data *data)
{
	long	t;

	t = data->last_meal + data->time_to_die - timestamp();
	if (t > 0)
		usleep(t * 1000);
	print_action(data, DEAD);
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
