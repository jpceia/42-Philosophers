/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/29 04:06:52 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <signal.h>

void	*check_starving(void *ptr)
{
	t_data	*data;
	int		index;

	data = (t_data *)ptr;
	while (timestamp() - data->last_meal < data->time_to_die && !data->stop)
		usleep(1000 * data->time_to_check);
	if (!data->stop)
	{
		index = 0;
		while (index++ < data->nb_philo)
			semaphore_post(data->set_stop);
		print_action(data, DEAD);
	}
	return (NULL);
}

void	*set_stop(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	semaphore_wait(data->set_stop);
	data->stop = 1;
	return (NULL);
}

void	do_think(t_data *data)
{
	print_action(data, THINK);
	usleep(1000 * data->time_to_think);
}

void	do_eat(t_data *data)
{
	if (!data->stop)
	{
		print_action(data, EAT);
		data->last_meal = timestamp();
		usleep(data->time_to_eat * 1000);
		data->nb_meals++;
	}
}

void	do_release_forks(t_data *data)
{
	semaphore_post(data->forks);
	semaphore_post(data->forks);
}

void	do_sleep(t_data *data)
{
	print_action(data, SLEEP);
	usleep(data->time_to_sleep * 1000);
}
