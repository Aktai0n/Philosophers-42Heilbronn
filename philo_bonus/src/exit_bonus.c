/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:16:57 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/28 20:36:26 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	ft_exit(t_data *data, const char *message)
{
	if (data->print_lock != NULL && data->print_lock != SEM_FAILED)
		sem_close(data->print_lock);
	if (data->forks != NULL && data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->start_lock != NULL && data->start_lock != SEM_FAILED)
		sem_close(data->start_lock);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}
