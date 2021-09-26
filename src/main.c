/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:20:19 by jceia             #+#    #+#             */
/*   Updated: 2021/09/26 02:16:04 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#include "philosophers.h"

/*
 * number_of_philosophers:
 *      is the number of philosophers and also the number of forks.
 * time_to_die
 *		is in milliseconds, if a philosopher doesn’t start eating
 *		’time_to_die’ milliseconds after starting his last meal or the
 *		beginning of the simulation, it dies
 * time_to_eat
 * 		is in milliseconds and is the time it takes for a philosopher to eat.
 * 		During that time he will need to keep the two forks.
 * time_to_sleep
 * 		is in milliseconds and is the time the philosopher will spend
 * 		sleeping.
 */


int	main(int argc, char **argv)
{
	int			index;
	t_args		args;
	t_shared	shared;
	t_data		*data;
	pthread_t	*thread;

	args_init(&args, argc, argv);
	shared_init(&shared, args.nb_philosophers);
	threads_init(&thread, data, &shared, &args);
	index = 0;
	while (index < args.nb_philosophers)
	{
		pthread_join(thread[index++], (void *)data);
		free(data);
	}
	free(thread);
	shared_clean(&shared);
	return (EXIT_SUCCESS);
}
