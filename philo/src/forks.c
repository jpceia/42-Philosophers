/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:42:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 21:23:44 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	forks_indexes(int index[2], int pos, int size)
{
	int	holder;

	index[0] = (pos - 1) % size;
	index[1] = pos % size;
	if (index[1] < index[0])
	{
		holder = index[0];
		index[0] = index[1];
		index[1] = holder;
	}
}

t_bool	forks_release(t_data *data)
{
	print_action(data, RELEASE_FORK);
	if (pthread_mutex_unlock(data->left_fork) != 0)
	{
		perror(MUTEX_UNLOCK_ERR);
		return (false);
	}
	if (pthread_mutex_unlock(data->right_fork) != 0)
	{
		perror(MUTEX_UNLOCK_ERR);
		return (false);
	}
	return (true);
}
