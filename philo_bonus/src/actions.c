/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 06:08:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 10:49:29 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <signal.h>

// https://unix.stackexchange.com/questions/124127/kill-all-descendant-processes
void	do_stop(t_data *data)
{
	(void)data;
	kill(0, SIGKILL);
}

void	do_dead(t_data *data)
{
	print_action(data, DEAD);
	do_stop(data);
}

t_bool	try_eat(t_data *data, sem_t *semaphore)
{
	long	t;

	sem_wait(semaphore);
	t = get_chrono(data->start_time);
	if (t - data->last_meal > data->time_to_die)
	{
		do_dead(data);
		return (false);
	}
	print_action(data, EAT);
	usleep(data->time_to_sleep * 1000);
	data->last_meal = get_chrono(data->start_time);
	data->nb_meals++;
	sem_post(semaphore);
	return (true);
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
