/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:05 by jceia             #+#    #+#             */
/*   Updated: 2021/10/24 13:53:23 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	*routine(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		if (try_eat(data) < 0)
			break ;
		if (data->shared->stop)
			break ;
		if (do_sleep(data) < 0)
			break ;
		if (data->shared->stop)
			break ;
		if (do_think(data) < 0)
			break ;
	}
	free(data);
	return (NULL);
}

int	try_eat(t_data *data)
{
	t_shared	*shared;

	shared = data->shared;
	if (shared->nb_philo == 1)
		return (-1);
	if (do_take_forks(data) < 0)
		return (-1);
	if (do_eat(data) < 0)
		return (-1);
	if (do_release_forks(data) < 0)
		return (-1);
	return (0);
}

t_bool	check_philosophers_dead(t_shared *shared, t_args *args)
{
	int		index;

	index = 0;
	while (index < args->nb_philo)
	{
		if (shared->last_meal[index] + args->time_to_die < timestamp())
		{
			pthread_mutex_lock(&shared->stop_mutex);
			if (!shared->stop)
			{
				shared->stop = true;
				print_action(index + 1, DEAD);
			}
			pthread_mutex_unlock(&shared->stop_mutex);
			return (true);
		}
		index++;
	}
	chrono(args->time_to_check);
	return (false);
}
