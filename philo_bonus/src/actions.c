/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/29 03:52:53 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <signal.h>

void	do_die(t_data *data)
{
	print_action(data, DEAD);
	kill(0, SIGTERM);
}

void	do_think(t_data *data)
{
	print_action(data, THINK);
	usleep(1000 * data->time_to_think);
}

void	do_eat(t_data *data)
{
	print_action(data, EAT);
	data->last_meal = timestamp();
	usleep(data->time_to_eat * 1000);
	data->nb_meals++;
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
