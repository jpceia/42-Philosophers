/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:58:13 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 16:14:09 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_bool	is_satisfied(t_data *data)
{
	if (data->max_meals > 0 && data->nb_meals == data->max_meals)
	{
		print_action(data, SATISFIED);
		data->shared->nb_satisfied++;
		if (data->shared->nb_satisfied == data->shared->nb_philo)
			do_stop(data->shared);
		return (true);
	}
	return (false);
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
