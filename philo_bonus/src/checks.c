/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 04:46:12 by jceia             #+#    #+#             */
/*   Updated: 2021/10/29 04:46:29 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_satisfied(void *ptr)
{
	t_data	*data;
	int		index;

	data = (t_data *)ptr;
	index = 0;
	while (index++ < data->nb_philo && !data->stop)
		semaphore_wait(data->satisfied);
	index = 0;
	semaphore_wait(data->set_stop_mutex);
	while (index++ < data->nb_philo + 1)
		semaphore_post(data->set_stop);
	usleep(100);
	semaphore_post(data->set_stop_mutex);
	return (NULL);
}

void	*check_starving(void *ptr)
{
	t_data	*data;
	int		index;

	data = (t_data *)ptr;
	while (timestamp() - data->last_meal < data->time_to_die && !data->stop)
		usleep(1000 * data->time_to_check);
	semaphore_wait(data->set_stop_mutex);
	if (!data->stop)
	{
		index = 0;
		while (index++ < data->nb_philo + 1)
			semaphore_post(data->set_stop);
		print_action(data, DEAD);
		usleep(100);
	}
	semaphore_post(data->set_stop_mutex);
	return (NULL);
}

void	*check_stop(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	semaphore_wait(data->set_stop);
	data->stop = 1;
	return (NULL);
}
