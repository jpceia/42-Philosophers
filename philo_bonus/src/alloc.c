/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:03:01 by jceia             #+#    #+#             */
/*   Updated: 2021/10/12 14:14:36 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <fcntl.h>

t_vars  *init_vars(t_vars *vars, int size)
{
	memset(vars, 0, sizeof(*vars));
	sem_unlink(SEM_NAME);
	vars->semaphore = sem_open(SEM_NAME, O_CREAT, 0644, size);
	if (vars->semaphore == SEM_FAILED)
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
	if (vars->semaphore)
	{
		sem_close(vars->semaphore);
		vars->semaphore = NULL;
	}
	if (unlink)
		sem_unlink(SEM_NAME);
	if (err_msg)
	{
		perror(err_msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
