/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:47:31 by jceia             #+#    #+#             */
/*   Updated: 2021/10/30 19:55:40 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <sys/wait.h>
#include <stdio.h>

void	main_loop(t_data *data, int index)
{
	data->pid[index] = fork();
	if (data->pid[index] < 0)
	{
		data_clean(data, FORK_ERR, 1);
		exit(EXIT_FAILURE);
	}
	if (data->pid[index] == 0)
	{
		data_setup_private(data, index + 1);
		routine(data);
		pthread_join(data->thread_stop, NULL);
		pthread_join(data->thread_starving, NULL);
		data_clean(data, NULL, 0);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	int			index;
	t_data		data;
	pthread_t	thread[2];

	if (!data_init(&data, argc, argv))
		return (EXIT_FAILURE);
	data.time_to_think = 0.1;
	data.time_to_check = 0.1;
	index = 0;
	timestamp();
	pthread_create(&thread[0], NULL, &check_stop, &data);
	pthread_create(&thread[1], NULL, &check_satisfied, &data);
	while (index < data.nb_philo)
		main_loop(&data, index++);
	index = 0;
	while (index < data.nb_philo)
		if (waitpid(data.pid[index++], NULL, 0) < 0)
			perror(WAITPID_ERR);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	data_clean(&data, NULL, 1);
	return (EXIT_SUCCESS);
}
