/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:38:19 by jceia             #+#    #+#             */
/*   Updated: 2021/10/10 13:35:54 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include "libft.h"

typedef enum e_state
{
	TAKE_FORK = 0,
	EAT,
	SLEEP,
	THINK,
	SATISFIED,
	DEAD,
}	t_state;

typedef struct s_shared
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks;
	int				nb_philo;
	int				nb_satisfied;
	long			start_time;
	t_bool			stop;
}	t_shared;

typedef struct s_args
{
	int		nb_philo;
	int		position;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
}	t_args;

typedef struct s_data
{
	t_shared	*shared;

	int			position;
	int			time_to_die;
	int			time_to_sleep;
	int			time_to_eat;
	int			nb_meals;
	int			max_meals;

	long		last_meal;
}	t_data;

/*
 * Utils
 */
t_args			*parse_args(t_args *args, int argc, char **argv);
long			get_chrono(long start_time);
void			print_action(t_data *data, t_state state);

/*
 * Actions
 */
void			do_stop(t_shared *shared);
void			do_die(t_data *data);
t_bool			try_eat(t_data *data);
void			do_think(t_data *data);
void			do_sleep(t_data *data);

void			*routine(void *ptr);

/*
 * Data Allocation
 */

pthread_mutex_t	*mutex_array_init(pthread_mutex_t **arr, int size);
void			mutex_array_destroy(pthread_mutex_t *arr, int size);

t_shared		*shared_init(t_shared *shared, int nb_philo);
void			shared_clean(t_shared *shared);

t_data			*data_init(t_data **data, t_shared *shared,
					const t_args *args, int position);

pthread_t		*threads_init(pthread_t **threads,
					t_shared *shared, t_args *args);

void			threads_join(pthread_t *threads, int size);

#endif