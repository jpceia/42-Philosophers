/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:03:01 by jceia             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/28 16:57:58 by jceia            ###   ########.fr       */
=======
/*   Updated: 2021/10/29 04:55:20 by jceia            ###   ########.fr       */
>>>>>>> ffd2f5a7ee5e22c845bd3e2fd393f23e58d53e3a
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>

t_data	*data_setup_public(t_data *data)
{
	data->forks = semaphore_create("/forks", data->nb_philo);
<<<<<<< HEAD
	data->print = semaphore_create("/print", 1);
	data->waiter = semaphore_create("/waiter", 1);
	if (!data->forks || !data->print || !data->waiter)
=======
	data->set_stop = semaphore_create("/set_stop", 0);
	data->print = semaphore_create("/print", 1);
	data->waiter = semaphore_create("/waiter", 1);
	data->set_stop_mutex = semaphore_create("/set_stop_mutex", 1);
	data->satisfied = semaphore_create("/satisfied", 0);
	if (!data->forks || !data->print || !data->set_stop
		|| !data->waiter || !data->set_stop_mutex
		|| !data->satisfied)
>>>>>>> ffd2f5a7ee5e22c845bd3e2fd393f23e58d53e3a
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
	pthread_create(&data->thread_stop, NULL, &check_stop, data);
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
<<<<<<< HEAD
=======
	semaphore_close(&data->set_stop, unlink);
>>>>>>> ffd2f5a7ee5e22c845bd3e2fd393f23e58d53e3a
	semaphore_close(&data->print, unlink);
	semaphore_close(&data->waiter, unlink);
	semaphore_close(&data->set_stop_mutex, unlink);
	semaphore_close(&data->satisfied, unlink);
	if (err_msg)
	{
		perror(err_msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
