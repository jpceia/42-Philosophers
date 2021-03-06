/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:25:20 by jceia             #+#    #+#             */
/*   Updated: 2022/03/31 18:40:37 by jpceia           ###   ########.fr       */
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

void	chrono(float t)
{
	usleep((int)(t * 1000));
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
	if (args->nb_philo <= 0 || args->time_to_die <= 0
		|| args->time_to_eat < 0 || args->time_to_sleep < 0
		|| args->meals_must_eat < 0)
	{
		ft_putstr_error("Invalid parameters, please provide"\
			" positive integers as arguments\n");
		return (NULL);
	}
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

void	print_action(int position, t_state state, pthread_mutex_t *mtx)
{
	char	*s;
	char	msg[BUF_SIZE];

	msg[0] = '\0';
	pthread_mutex_lock(mtx);
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
	pthread_mutex_unlock(mtx);
}
