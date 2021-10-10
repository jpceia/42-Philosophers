/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:47:31 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 10:49:46 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "philosophers.h"

/*
 * Allowed functions
 * processes
 *	  fork
 *	  kill
 *	  waitpid
 * semaphores
 *	  sem_open
 *	  sem_close
 *	  sem_post
 *	  sem_wait
 *	  sem_unlink
 */

// kill main process when a child dies
t_bool	is_satisfied(t_data *data)
{
	if (data->max_meals > 0)
	{
		if (data->nb_meals == data->max_meals)
		{
			print_action(data, SATISFIED);
			do_stop(data);
		}
	}
}

void	routine(t_data *data, sem_t *semaphore)
{
	while (1)
	{
		if (!try_eat(data, semaphore))
			break ;
		if (is_satisfied(data))
			break ;
		do_sleep(data);
		do_think(data);
	}
}

// https://stackoverflow.com/questions/32205396/share-posix-semaphore-among-multiple-processes
int	main(int argc, char *argv[])
{
	int		index;
	pid_t	*pid;
	t_data	data;
	sem_t	*semaphore;

	parse_data(&data, argc, argv);
	// sem_init(&semaphore, 1, data.nb_philo / 2);
	semaphore = sem_open(SEM_NAME, O_CREAT, SEM_PERMS, data.nb_philo);
	pid = malloc(data.nb_philo * sizeof(*pid));
	index = 0;
	while (index < data.nb_philo)
	{
		pid[index] = fork();
		if (pid[index] == -1)
		{
			perror("Error with creating process");
			return (EXIT_FAILURE);
		}
		if (pid[index] == 0)
		{
			data.position = index;
			routine(&data, semaphore);
			return (EXIT_SUCCESS);
		}
		index++;
	}
	index = 0;
	while (index < data.nb_philo)
	{
		waitpid(pid[index], NULL, 0);
		index++;
	}
	sem_close(semaphore);
	return (EXIT_SUCCESS);
}
