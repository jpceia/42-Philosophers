/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:47:31 by jceia             #+#    #+#             */
/*   Updated: 2021/10/29 03:52:01 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <sys/wait.h>

void	main_loop(t_data *data, int index)
{
	data->pid[index] = fork();
	if (data->pid[index] < 0)
		exit(data_clean(data, "fork(2) failed", 1));
	if (data->pid[index] == 0)
	{
		data->position = index + 1;
		routine(data);
		exit(data_clean(data, NULL, 0));
	}
}

int	main(int argc, char *argv[])
{
	int		index;
	t_data	data;

	if (!data_init(&data, argc, argv))
		return (EXIT_FAILURE);
	index = 0;
	timestamp();
	while (index < data.nb_philo)
		main_loop(&data, index++);
	index = 0;
	while (index < data.nb_philo)
		if (waitpid(data.pid[index++], NULL, 0) < 0)
			perror("waitpid(2) failed");
	data_clean(&data, NULL, 1);
	return (EXIT_SUCCESS);
}
