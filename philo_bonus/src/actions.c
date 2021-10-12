/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 15:46:28 by jceia            ###   ########.fr       */
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
}

void	do_take_fork(t_data *data)
{
	print_action(data, TAKE_FORK);
}

void	do_eat(t_data *data)
{
	print_action(data, EAT);
	data->last_meal = get_chrono(0) - data->start_time;
	usleep(data->time_to_eat * 1000);
	data->nb_meals++;
}

void	do_release_fork(t_data *data)
{
	print_action(data, RELEASE_FORK);
}

void	do_sleep(t_data *data)
{
	print_action(data, SLEEP);
	usleep(data->time_to_sleep * 1000);
}
