/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 09:31:49 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

int	do_stop(t_shared *shared)
{
	if (pthread_mutex_lock(&shared->stop_mutex) != 0)
	{
		perror(MUTEX_LOCK_ERR);
		return (EXIT_FAILURE);
	}
	shared->stop = true;
	if (pthread_mutex_unlock(&shared->stop_mutex) != 0)
	{
		perror(MUTEX_LOCK_ERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	do_die(t_data *data)
{
	print_action(data, DEAD);
	return (do_stop(data->shared));
}

int	do_eat(t_data *data)
{
	print_action(data, EAT);
	usleep(data->time_to_eat * 1000);
	data->last_meal = get_chrono(0) - data->shared->start_time;
	data->nb_meals++;
	return (0);
}

int	do_think(t_data *data)
{
	print_action(data, THINK);
	return (0);
}

int	do_sleep(t_data *data)
{
	print_action(data, SLEEP);
	usleep(data->time_to_sleep * 1000);
	return (0);
}
