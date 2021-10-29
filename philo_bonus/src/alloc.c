/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:03:01 by jceia             #+#    #+#             */
/*   Updated: 2021/10/29 04:06:12 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>

t_data	*data_setup_public(t_data *data)
{
	data->forks = semaphore_create("/forks", data->nb_philo);
	data->set_stop = semaphore_create("/set_stop", 0);
	data->print = semaphore_create("/print", 1);
	data->waiter = semaphore_create("/waiter", 1);
	if (!data->forks || !data->print || !data->set_stop || !data->waiter)
	{
		data_clean(data, "", 1);
		return (NULL);
	}
	data->pid = malloc(data->nb_philo * sizeof(*data->pid));
	if (!data->pid)
	{
		data_clean(data, MALLOC_ERR, 1);
		return (NULL);
	}
	return (data);
}

t_data	*data_setup_private(t_data *data, int position)
{
	data->position = position;
	pthread_create(&data->thread_stop, NULL, &set_stop, data);
	pthread_create(&data->thread_starving, NULL, &check_starving, data);
	return (data);
}

t_data	*data_init(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(*data));
	if (argc != 5 && argc != 6)
	{
		ft_putstr_error("Incorrect number of arguments\n");
		return (NULL);
	}
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	return (data_setup_public(data));
}

int	data_clean(t_data *data, char *err_msg, t_bool unlink)
{
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	semaphore_close(&data->forks, unlink);
	semaphore_close(&data->set_stop, unlink);
	semaphore_close(&data->print, unlink);
	semaphore_close(&data->waiter, unlink);
	if (err_msg)
	{
		perror(err_msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
