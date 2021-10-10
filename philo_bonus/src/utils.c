/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:25:20 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 10:50:04 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "philosophers.h"
#include "libft.h"

long	get_chrono(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

t_data	*parse_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		return (NULL);
	}
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_meals = 0;
	data->max_meals = 0;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	return (data);
}

void	print_action(t_data *data, t_state state)
{
	long	t;
	char	*s;

	t = get_chrono(data->start_time);
	if (state == EAT)
		s = " is eating";
	else if (state == THINK)
		s = " is thinking";
	else if (state == SLEEP)
		s = " is sleeping";
	else if (state == SATISFIED)
		s = " is satisfied";
	else if (state == DEAD)
		s = " died";
	else
		return ;
	ft_putnbr((int)t);
	ft_putstr("ms philosoper ");
	ft_putnbr(data->position);
	ft_putstr(s);
	ft_putchar('\n');
}
