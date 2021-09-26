/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 01:58:10 by jceia             #+#    #+#             */
/*   Updated: 2021/09/26 01:58:50 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>


void	forks_lock(t_data *data)
{
	int	nb;
	int i;
	int j;

	nb = data->shared->nb_philosophers;
	i = data->position % nb;
	j = (data->position + 1) % nb;
	data->shared->forks[i] = 1;
	data->shared->forks[j] = 1;
}

void	forks_unlock(t_data *data)
{
	int	nb;
	int	i;
	int	j;

	nb = data->shared->nb_philosophers;
	i = data->position % nb;
	j = (data->position + 1) % nb;
	data->shared->forks[i] = 0;
	data->shared->forks[j] = 0;
}

t_bool	forks_avail(const t_data *data)
{
	t_bool *forks;
	int		nb;
	int		i;
	int		j;

	nb = data->shared->nb_philosophers;
	forks = data->shared->forks;
	i = data->position % nb;
	j = (data->position + 1) % nb;
	return ((forks[i] == 0) && (forks[j] == 0));
}
