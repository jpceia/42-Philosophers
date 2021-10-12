/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:53:03 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 14:03:13 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_data *data, sem_t *semaphore)
{
	while (1)
	{
		if (!try_eat(data, semaphore))
			break ;
		if (is_satisfied(data))
			break ;
		do_sleep(data);
		if (check_if_dead(data))
			break;
		do_think(data);
	}
}

