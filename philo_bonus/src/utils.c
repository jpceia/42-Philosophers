/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:25:20 by jceia             #+#    #+#             */
/*   Updated: 2021/10/28 18:18:48 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philosophers.h"
#include "libft.h"

long	get_chrono(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

char	*state_message(t_state state)
{
	if (state == TAKE_FORK)
		return ("has taken a fork");
	if (state == EAT)
		return ("is eating");
	if (state == RELEASE_FORKS)
		return ("has released his forks");
	if (state == SLEEP)
		return ("is sleeping");
	if (state == THINK)
		return ("is thinking");
	if (state == SATISFIED)
		return ("is satisfied");
	if (state == DEAD)
		return ("died");
	return ("(unkown action)");
}

void	print_action(t_data *data, t_state state)
{
	long	t;

	t = get_chrono(data->start_time);
	semaphore_wait(data->print);
	ft_putnbr((int)t);
	ft_putstr("\t");
	ft_putnbr(data->position);
	ft_putchar(' ');
	ft_putendl(state_message(state));
	if (state != DEAD)
		semaphore_post(data->print);
}
