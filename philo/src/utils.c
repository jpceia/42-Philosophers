/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:25:20 by jceia             #+#    #+#             */
/*   Updated: 2021/10/24 12:52:09 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philosophers.h"
#include "libft.h"

long	timestamp(void)
{
	static long		start_time = 0;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (start_time == 0)
	{
		start_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

t_args	*parse_args(t_args *args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_error("Incorrect number of arguments\n");
		return (NULL);
	}
	args->nb_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->meals_must_eat = 0;
	if (argc == 6)
		args->meals_must_eat = ft_atoi(argv[5]);
	return (args);
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

void	print_action(int position, t_state state)
{
	char	*s;
	char	msg[BUF_SIZE];

	msg[0] = '\0';
	s = ft_itoa((int)timestamp());
	ft_strlcat(msg, s, BUF_SIZE);
	free(s);
	ft_strlcat(msg, "\t", BUF_SIZE);
	s = ft_itoa(position);
	ft_strlcat(msg, s, BUF_SIZE);
	free(s);
	ft_strlcat(msg, " ", BUF_SIZE);
	s = state_message(state);
	ft_strlcat(msg, s, BUF_SIZE);
	ft_strlcat(msg, "\n", BUF_SIZE);
	ft_putstr(msg);
}
