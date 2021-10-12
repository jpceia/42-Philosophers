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

void	main_loop(t_vars *vars, t_data *data, int index)
{
	vars->pid[index] = fork();
	if (vars->pid[index] < 0)
		exit(clean_vars(vars, "fork(2) failed", 1));
	if (vars->pid[index] == 0)
	{
		data->position = index + 1;
		routine(data, vars->semaphore);
		exit(clean_vars(vars, NULL, 0));
	}
}

// https://stackoverflow.com/questions/32205396/share-posix-semaphore-among-multiple-processes
int	main(int argc, char *argv[])
{
	int		index;
	t_data	data;
	t_vars	vars;

	if (!parse_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (!init_vars(&vars, data.nb_philo))
		return (EXIT_FAILURE);
	index = 0;
	while (index < data.nb_philo)
		main_loop(&vars, &data, index++);
	index = 0;
	while (index < data.nb_philo)
		if (waitpid(vars.pid[index++], NULL, 0) < 0)
			perror("waitpid(2) failed");
	clean_vars(&vars, NULL, 1);
	return (EXIT_SUCCESS);
}
