/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:12:00 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/29 00:30:03 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	eating_state(t_philo *philo)
{
	philo->state = taking_a_fork;
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, philo->state, &philo->data->print_lock);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, philo->state, &philo->data->print_lock);
	philo->state = eating;
	print_state(philo, philo->state, &philo->data->print_lock);
	philo->death_time = timestamp_ms() + (uint64_t)philo->data->time_to_die;
	if (philo->data->max_num_eat > 0)
		philo->num_eat--;
	wait_ms(philo->data->time_to_eat, philo->data->num_philos);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	sleeping_state(t_philo *philo)
{
	philo->state = sleeping;
	print_state(philo, philo->state, &philo->data->print_lock);
	wait_ms(philo->data->time_to_sleep, philo->data->num_philos);
}

static void	thinking_state(t_philo *philo)
{
	philo->state = thinking;
	print_state(philo, philo->state, &philo->data->print_lock);
}

void	*philo_loop(void *attr)
{
	t_philo	*philo;

	philo = (t_philo *)attr;
	while (philo->data->running == FALSE)
		continue ;
	philo->death_time = timestamp_ms() + (uint64_t)philo->data->time_to_die;
	if (philo->data->num_philos == 1)
	{
		print_state(philo, taking_a_fork, &philo->data->print_lock);
		wait_ms(philo->data->time_to_die + 10, philo->data->num_philos);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		wait_ms(philo->data->time_to_eat / 2, philo->data->num_philos);
	while (philo->data->running == TRUE && philo->num_eat != 0)
	{
		if (philo->state == thinking)
			eating_state(philo);
		else if (philo->state == eating)
			sleeping_state(philo);
		else if (philo->state == sleeping)
			thinking_state(philo);
	}
	return (NULL);
}

void	*ft_mortis(void *attr)
{
	const t_philo	*all_philo;
	t_data			*data;
	int				i;

	all_philo = (const t_philo *)attr;
	data = all_philo->data;
	data->start_time = timestamp_ms();
	data->running = TRUE;
	wait_ms(data->time_to_die / 2, data->num_philos);
	while (TRUE)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (timestamp_ms() > all_philo[i].death_time)
			{
				data->running = FALSE;
				print_state(all_philo + i, dead, &data->print_lock);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
