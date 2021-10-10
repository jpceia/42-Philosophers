/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:58:13 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 06:19:17 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_bool	is_satisfied(t_data *data)
{
	if (data->max_meals > 0)
	{
		if (data->nb_meals == data->max_meals)
		{
			print_action(data, SATISFIED);
			pthread_mutex_lock(&data->shared->stop_mutex);
			data->shared->stop = true;
			pthread_mutex_unlock(&data->shared->stop_mutex);
		}
	}
}

void	*routine(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		if (!try_eat(data))
			break ;
		if (data->shared->stop)
			break ;
		if (is_satisfied(data))
			break ;
		do_sleep(data);
		if (data->shared->stop)
			break ;
		do_think(data);
	}
	return ((void *)data);
}
