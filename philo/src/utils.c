/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:25:20 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 16:40:45 by jceia            ###   ########.fr       */
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

t_args	*parse_args(t_args *args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		return (NULL);
	}
	args->nb_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->max_meals = 0;
	if (argc == 6)
		args->max_meals = ft_atoi(argv[5]);
	return (args);
}

void	print_action(t_data *data, t_state state)
{
	long	t;
	char	*s;
	char	msg[BUF_SIZE];

	t = get_chrono(data->shared->start_time);
	msg[0] = '\0';
	s = ft_itoa((int)t);
	ft_strlcat(msg, s, BUF_SIZE);
	free(s);
	ft_strlcat(msg, "\tphilosopher ", BUF_SIZE);
	s = ft_itoa(data->position);
	ft_strlcat(msg, s, BUF_SIZE);
	free(s);
	ft_strlcat(msg, "\t", BUF_SIZE);
	if (state == TAKE_FORK)
		s = "has taken a fork";
	else if (state == EAT)
		s = "is eating";
	else if (state == SLEEP)
		s = "is sleeping";
	else if (state == THINK)
		s = "is thinking";
	else if (state == SATISFIED)
		s = "is satisfied";
	else if (state == DEAD)
		s = "died";
	else
		s = "(unkown action)";
	ft_strlcat(msg, s, BUF_SIZE);
	ft_strlcat(msg, " ", BUF_SIZE);
	s = ft_itoa(data->shared->nb_satisfied);
	ft_strlcat(msg, s, BUF_SIZE);
	free(s);
	ft_strlcat(msg, "\n", BUF_SIZE);
	ft_putstr(msg);
}
