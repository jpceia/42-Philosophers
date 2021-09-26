/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:38:19 by jceia             #+#    #+#             */
/*   Updated: 2021/09/26 02:16:49 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef enum e_bool
{
	false = 0,
	true
}	t_bool;

typedef	enum e_state
{
	THINK = 0,
	EAT,
	SLEEP,
	DEAD,
}	t_state;

typedef struct s_shared
{
	pthread_cond_t	cond;
	pthread_mutex_t	mutex;
	t_bool			*forks;
	t_bool			any_dead;
	long			ts_start;
	int				nb_philosophers;
}   t_shared;

typedef struct s_args
{
	int		nb_philosophers;
	int		position;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eats;
}	t_args;

typedef struct s_data
{
    t_shared	*shared;

	int			position;
	int			time_to_die;
	int			time_to_sleep;
	int			time_to_eat;
	int			nb_eats;

	long	last_meal;
	t_bool	dead;
}	t_data;

void	shared_init(t_shared *shared, int nb_philosophers);
void	data_init(t_data **data, t_shared *shared,
		const t_args *args, int position);
void	args_init(t_args *args, int argc, char **argv);
void	threads_init(pthread_t **t, t_data *data, t_shared *shared, t_args *args);
void	shared_clean(t_shared *shared);

void	forks_lock(t_data *data);
void	forks_unlock(t_data *data);
t_bool	forks_avail(const t_data *data);

long	get_ts_milliseconds(long ts_start);
void	*philosopher_routine(void *ptr);

#endif