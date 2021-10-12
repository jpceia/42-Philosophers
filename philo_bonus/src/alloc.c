/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:03:01 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 16:00:32 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>

t_data	*data_setup(t_data *data)
{
	sem_unlink(SEM_NAME_1);
	data->forks = sem_open(SEM_NAME_1, O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
	{
		data_clean(data, "sem_open(3) error", 1);
		return (NULL);
	}
	sem_unlink(SEM_NAME_2);
	data->stop = sem_open(SEM_NAME_2, O_CREAT, 0644, 1);
	if (data->stop == SEM_FAILED)
	{
		data_clean(data, "sem_open(3) error", 1);
		return (NULL);
	}
	data->pid = malloc(data->nb_philo * sizeof(*data->pid));
	if (!data->pid)
	{
		data_clean(data, "malloc(3) failed", 1);
		return (NULL);
	}
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
	data->start_time = get_chrono(0);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	return (data_setup(data));
}

int	data_clean(t_data *data, char *err_msg, t_bool unlink)
{
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	if (data->forks)
	{
		sem_close(data->forks);
		data->forks = NULL;
	}
	if (data->stop)
	{
		sem_close(data->stop);
		data->stop = NULL;
	}
	if (unlink)
		sem_unlink(SEM_NAME_1);
	if (unlink)
		sem_unlink(SEM_NAME_2);
	if (err_msg)
	{
		perror(err_msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
