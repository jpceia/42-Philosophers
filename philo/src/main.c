/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:20:19 by jceia             #+#    #+#             */
/*   Updated: 2022/03/31 17:28:16 by jpceia           ###   ########.fr       */
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

	if (!parse_args(&args, argc, argv))
		return (EXIT_FAILURE);
	args.time_to_think = 0.1;
	args.time_to_check = 0.1;
	if (shared_init(&shared, args.nb_philo) == NULL)
	{
		ft_putstr_error("Error initializing variable\n");
		shared_clean(&shared);
		return (EXIT_FAILURE);
	}
	if (threads_init(&thread, &shared, &args) == NULL)
	{
		ft_putstr_error("Error initializing threads\n");
		shared_clean(&shared);
		return (EXIT_FAILURE);
	}
	while (!check_philosophers_dead(&shared, &args))
		chrono(args.time_to_check);
	threads_join(thread, args.nb_philo);
	shared_clean(&shared);
	return (EXIT_SUCCESS);
}
