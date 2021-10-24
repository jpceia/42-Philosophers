/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:38:19 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 16:07:37 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include "libft.h"

# define BUF_SIZE	1024

# define MALLOC_ERR			"malloc(3) error"
# define MUTEX_INIT_ERR		"pthread_mutex_init(3) error"
# define MUTEX_DESTROY_ERR	"pthread_mutex_destroy(3) error"
# define MUTEX_LOCK_ERR		"pthread_mutex_lock(3) error"
# define MUTEX_UNLOCK_ERR	"pthread_mutex_unlock(3) error"
# define THREAD_CREATE_ERR	"pthread_create(3) error"
# define THREAD_DETACH_ERR	"pthread_detach(3) error"
# define THREAD_JOIN_ERR	"pthread_join(3) error"

typedef enum e_state
{
	TAKE_FORK = 0,
	RELEASE_FORKS,
	EAT,
	SLEEP,
	THINK,
	SATISFIED,
	DEAD,
}	t_state;

typedef struct s_shared
{
	pthread_mutex_t	last_meal_mutex;
	long			*last_meal;

	pthread_mutex_t	satisfied_mutex;
	int				nb_satisfied;

	pthread_mutex_t	stop_mutex;
	t_bool			stop;

	pthread_mutex_t	*forks;

	int				nb_philo;
	long			start_time;
}	t_shared;

typedef struct s_args
{
	int				nb_philo;
	int				position;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	float			time_to_think;
	int				meals_must_eat;
	float			time_to_check;
}	t_args;

typedef struct s_data
{
	t_shared		*shared;

	int				position;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	float			time_to_think;
	int				nb_meals;
	int				meals_must_eat;
	long			last_meal;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_data;

/*
 * Utils
 */
t_args			*parse_args(t_args *args, int argc, char **argv);
long			timestamp(void);
void			print_action(int position, t_state state);

/*
 * Routine
 */
void			*routine(void *ptr);
int				try_eat(t_data *data);
t_bool			check_if_dead(t_data *data);
void			one_philo_die(t_data *data);
t_bool			check_philosophers_dead(t_shared *shared, t_args *args);

/*
 * Actions
 */
int				do_die(t_data *data);
int				do_think(t_data *data);
int				do_eat(t_data *data);
int				do_take_forks(t_data *data);
int				do_release_forks(t_data *data);
int				do_sleep(t_data *data);

/*
 * Forks
 */
void			forks_indexes(int index[2], int pos, int size);

/*
 * Data Allocation & clear
 */
pthread_mutex_t	*mutex_array_init(pthread_mutex_t **arr, int size);
void			mutex_array_destroy(pthread_mutex_t *arr, int size);

t_shared		*shared_init(t_shared *shared, int nb_philo);
void			shared_clean(t_shared *shared);

t_data			*data_init(t_data **data, t_shared *shared,
					const t_args *args, int position);

/*
 * Threads
 */

pthread_t		*threads_init(pthread_t **threads,
					t_shared *shared, t_args *args);

void			threads_join(pthread_t *thread, int size);

#endif