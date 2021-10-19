/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   named_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:56:05 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 16:58:13 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>

t_semaphore	*semaphore_create(char *name, int value)
{
	t_semaphore	*p;

	p = malloc(sizeof(*p));
	if (!p)
	{
		perror(MALLOC_ERR);
		return (NULL);
	}
	sem_unlink(name);
	p->name = name;
	p->sem = sem_open(name, O_CREAT, 0644, value);
	if (p->sem == SEM_FAILED)
	{
		perror(SEM_OPEN_ERR);
		return (NULL);
	}
	return (p);
}

void	semaphore_close(t_semaphore **ref, t_bool unlink)
{
	t_semaphore	*p;

	p = *ref;
	if (p)
	{
		sem_close(p->sem);
		if (unlink)
			sem_unlink(p->name);
		free(p);
		p = NULL;
	}
}

void	semaphore_post(t_semaphore *p)
{
	sem_post(p->sem);
}

void	semaphore_wait(t_semaphore *p)
{
	sem_wait(p->sem);
}
