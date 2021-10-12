/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:42:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 16:44:29 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

void	forks_indexes(int index[2], int pos, int size)
{
	int	holder;

	index[0] = pos % size;
	index[1] = (pos + 1) % size;
	if (index[1] < index[0])
	{
		holder = index[0];
		index[0] = index[1];
		index[1] = holder;
	}
}

void	forks_release(int index[2], pthread_mutex_t *forks)
{
	pthread_mutex_unlock(&forks[index[1]]);
	pthread_mutex_unlock(&forks[index[0]]);
}
