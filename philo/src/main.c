/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:20:19 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 16:07:53 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "philosophers.h"
#include "libft.h"

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
int	main(int argc, char *argv[])
{
	t_args		args;
	t_shared	shared;
	pthread_t	*thread;

	parse_args(&args, argc, argv);
	args.time_to_think = 0.1;
	args.time_to_check = 0.1;
	if (shared_init(&shared, args.nb_philo) < 0)
	{
		ft_putstr_error("Error initializing variable\n");
		shared_clean(&shared);
		return (EXIT_FAILURE);
	}
	if (threads_init(&thread, &shared, &args) < 0)
	{
		ft_putstr_error("Error initializing threads\n");
		shared_clean(&shared);
		return (EXIT_FAILURE);
	}
	while (1)
		if (check_philosophers_dead(&shared, &args))
			break ;
	threads_join(thread, args.nb_philo);
	shared_clean(&shared);
	return (EXIT_SUCCESS);
}
