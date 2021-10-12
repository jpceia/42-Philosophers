/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:03:01 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 15:00:58 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>

t_vars	*init_vars(t_vars *vars, int size)
{
	memset(vars, 0, sizeof(*vars));
	sem_unlink(SEM_NAME_1);
	vars->forks = sem_open(SEM_NAME_1, O_CREAT, 0644, size);
	if (vars->forks == SEM_FAILED)
	{
		clean_vars(vars, "sem_open(3) error", 1);
		return (NULL);
	}
	sem_unlink(SEM_NAME_2);
	vars->stop = sem_open(SEM_NAME_2, O_CREAT, 0644, 1);
	if (vars->stop == SEM_FAILED)
	{
		clean_vars(vars, "sem_open(3) error", 1);
		return (NULL);
	}
	vars->pid = malloc(size * sizeof(*vars->pid));
	if (!vars->pid)
	{
		clean_vars(vars, "malloc(3) failed", 1);
		return (NULL);
	}
	return (vars);
}

int	clean_vars(t_vars *vars, char *err_msg, t_bool unlink)
{
	if (vars->pid)
	{
		free(vars->pid);
		vars->pid = NULL;
	}
	if (vars->forks)
	{
		sem_close(vars->forks);
		vars->forks = NULL;
	}
	if (vars->stop)
	{
		sem_close(vars->stop);
		vars->stop = NULL;
	}
	if (unlink)
		sem_unlink(SEM_NAME_1);
	if (unlink)
		sem_unlink(SEM_NAME_2);
	if (err_msg)
	{
		perror(err_msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
