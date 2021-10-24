/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:42:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 15:15:10 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	forks_indexes(int index[2], int pos, int size)
{
	int	holder;

	index[0] = (pos - 1) % size;
	index[1] = pos % size;
	if (pos % 2 == 0)
	{
		holder = index[0];
		index[0] = index[1];
		index[1] = holder;
	}
}

int	do_release_forks(t_data *data)
{
	long	t;

	t = timestamp();
	if (pthread_mutex_unlock(data->fork1) != 0)
	{
		perror(MUTEX_UNLOCK_ERR);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(data->fork2) != 0)
	{
		perror(MUTEX_UNLOCK_ERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	do_take_forks(t_data *data)
{
	long	t;

	pthread_mutex_lock(data->fork1);
	if (data->shared->stop || check_if_dead(data))
	{
		pthread_mutex_unlock(data->fork1);
		return (-1);
	}
	t = timestamp();
	print_action(t, data->position, TAKE_FORK);
	pthread_mutex_lock(data->fork2);
	t = timestamp();
	print_action(t, data->position, TAKE_FORK);
	if (data->shared->stop || check_if_dead(data))
	{
		do_release_forks(data);
		return (-1);
	}
	return (0);
}
