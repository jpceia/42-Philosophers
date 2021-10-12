/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 16:37:41 by jceia            ###   ########.fr       */
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

void	do_eat(t_data *data)
{
	print_action(data, EAT);
	usleep(data->time_to_eat * 1000);
	data->last_meal = get_chrono(data->shared->start_time);
	data->nb_meals++;
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
