/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:16:57 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/27 18:25:51 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_exit(t_data *data, const char *message)
{
	if (data->forks != NULL)
		destroy_locks(data);
	ft_freeall();
	ft_putendl_fd(message, 2);
	return (RETURN_FAILURE);
}

void	destroy_locks(t_data *data)
{
	int	i;

	if (data->forks != NULL)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(data->forks + i);
			i++;
		}
		ft_free_1d((void **)&data->forks);
	}
	pthread_mutex_destroy(&data->print_lock);
}
