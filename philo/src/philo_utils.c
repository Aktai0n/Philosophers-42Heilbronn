/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:17:22 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/29 01:29:17 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

uint64_t	timestamp_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	wait_ms(uint64_t ms, int num_threads)
{
	uint64_t	end;

	end = timestamp_ms() + ms;
	while (timestamp_ms() < end)
		usleep(num_threads);
}

void	print_state(const t_philo *philo, const t_state state,
					pthread_mutex_t *print_lock)
{
	uint64_t	current_time;

	pthread_mutex_lock(print_lock);
	if (philo->data->running == TRUE || state == dead)
	{
		current_time = timestamp_ms() - philo->data->start_time;
		if (state == taking_a_fork)
			printf("%-5llu %-3d %s",
				current_time, philo->id, "has taken a fork\n");
		else if (state == eating)
			printf("%-5llu %-3d %s",
				current_time, philo->id, "is eating\n");
		else if (state == sleeping)
			printf("%-5llu %-3d %s",
				current_time, philo->id, "is sleeping\n");
		else if (state == thinking)
			printf("%-5llu %-3d %s",
				current_time, philo->id, "is thinking\n");
		else if (state == dead)
			printf("%-5llu %-3d %s",
				current_time, philo->id, "died\n");
	}
	pthread_mutex_unlock(print_lock);
}
