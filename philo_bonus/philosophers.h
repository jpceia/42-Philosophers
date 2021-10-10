/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:38:19 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 10:49:19 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include "libft.h"

# define SEM_NAME "./philo_semaphore"
# define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

typedef enum e_state
{
	THINK = 0,
	EAT,
	SLEEP,
	SATISFIED,
	DEAD,
}	t_state;

typedef struct s_data
{
	int		nb_philo;
	int		position;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
	int		nb_means;
	long	last_meal;
	long	start_time;
}	t_data;

/*
 * Utils
 */
t_data			*parse_data(t_data *data, int argc, char **argv);
long			get_chrono(long start_time);
void			print_action(t_data *data, t_state state);

/*
 * Actions
 */
void			do_stop(void);
void			do_dead(t_data *data);
t_bool			try_eat(t_data *data, sem_t *semaphore);
void			do_think(t_data *data);
void			do_sleep(t_data *data);

void			routine(t_data *data, sem_t *semaphore);

/*
 * Data Allocation
 */

#endif