/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:38:19 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 14:32:27 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include "libft.h"

# define SEM_NAME "/forks_semaphore"

# define BUF_SIZE 1024

typedef struct s_vars
{
	pid_t	*pid;
	sem_t	*semaphore;
}	t_vars;

t_vars	*init_vars(t_vars *vars, int size);
int		clean_vars(t_vars *vars, char *err_msg, t_bool unlink);

typedef enum e_state
{
	TAKE_FORK = 0,
	EAT,
	SLEEP,
	THINK,
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
	int		nb_meals;
	long	last_meal;
	long	start_time;
}	t_data;

/*
 * Utils
 */
t_data	*parse_data(t_data *data, int argc, char **argv);
long	get_chrono(long start_time);
void	print_action(t_data *data, t_state state);

/*
 * Actions
 */
void	routine(t_data *data, sem_t *semaphore);
t_bool	try_eat(t_data *data, sem_t *semaphore);
t_bool	check_if_dead(t_data *data);
t_bool	is_satisfied(t_data *data);
t_bool	one_philo_die(t_data *data);

void	do_die(t_data *data);
void	do_think(t_data *data);
void	do_eat(t_data *data);
void	do_sleep(t_data *data);

#endif