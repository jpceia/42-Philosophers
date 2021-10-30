/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:42:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/24 15:05:38 by jceia            ###   ########.fr       */
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
	pthread_mutex_unlock(data->fork1);
	pthread_mutex_unlock(data->fork2);
	return (0);
}

int	do_take_forks(t_data *data)
{
	pthread_mutex_lock(data->fork1);
	if (data->shared->stop)
	{
		pthread_mutex_unlock(data->fork1);
		return (-1);
	}
	print_action(data->position, TAKE_FORK);
	pthread_mutex_lock(data->fork2);
	if (data->shared->stop)
	{
		do_release_forks(data);
		return (-1);
	}
	print_action(data->position, TAKE_FORK);
	return (0);
}
