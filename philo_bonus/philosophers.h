/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:38:19 by jceia             #+#    #+#             */
/*   Updated: 2021/10/29 04:11:58 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <pthread.h>
# include "libft.h"

# define SEM_NAME_1 "/sem1"
# define SEM_NAME_2 "/sem2"

# define BUF_SIZE	1024

# define MALLOC_ERR		"malloc(3) failed"
# define SEM_OPEN_ERR	"sem_open(3) error"
# define FORK_ERR		"fork(2) failed"

typedef struct s_semaphore
{
	sem_t	*sem;
	char	*name;
}	t_semaphore;

typedef struct s_data
{
	int			nb_philo;
	int			position;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			nb_meals;
	long		last_meal;
	float		time_to_think;
	float		time_to_check;
	pid_t		*pid;
	t_bool		stop;

	t_semaphore	*forks;
	t_semaphore	*print;
	t_semaphore	*waiter;
	t_semaphore	*set_stop;
	t_semaphore	*set_stop_mutex;

	pthread_t	thread_starving;
	pthread_t	thread_stop;
}	t_data;

t_data		*data_init(t_data *data, int argc, char **argv);
t_data		*data_setup_private(t_data *data, int position);
int			data_clean(t_data *data, char *err_msg, t_bool unlink);
t_semaphore	*semaphore_create(char *name, int value);
void		semaphore_close(t_semaphore **p, t_bool unlink);
void		semaphore_post(t_semaphore *p);
void		semaphore_wait(t_semaphore *p);

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

/*
 * Utils
 */
long		timestamp(void);
void		print_action(t_data *data, t_state state);

/*
 * Actions
 */
void		routine(t_data *data);
void		*check_stop(void *ptr);
void		*check_starving(void *ptr);
t_bool		try_eat(t_data *data);
t_bool		check_if_stop(t_data *data);
t_bool		is_satisfied(t_data *data);
t_bool		one_philo_die(t_data *data);

void		do_think(t_data *data);
void		do_eat(t_data *data);
void		do_release_forks(t_data *data);
void		do_sleep(t_data *data);

#endif