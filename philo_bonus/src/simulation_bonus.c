/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:22:24 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/29 01:24:50 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

static void	eating_state(t_data *data)
{
	data->state = taking_a_fork;
	sem_wait(data->forks);
	print_state(data, data->state);
	sem_wait(data->forks);
	print_state(data, data->state);
	data->state = eating;
	print_state(data, data->state);
	if (data->num_eat > 0)
		data->num_eat--;
	data->death_time = timestamp_ms() + (uint64_t)data->time_to_die;
	wait_ms(data->time_to_eat, data->num_philos);
	sem_post(data->forks);
	sem_post(data->forks);
}

static void	sleeping_state(t_data *data)
{
	data->state = sleeping;
	print_state(data, data->state);
	wait_ms(data->time_to_sleep, data->num_philos);
}

static void	thinking_state(t_data *data)
{
	data->state = thinking;
	print_state(data, data->state);
}

static void	*ft_mortis(void *attr)
{
	t_data		*data;
	useconds_t	sleep_time;

	data = (t_data *)attr;
	sleep_time = (useconds_t)(data->num_philos * 50);
	while (TRUE)
	{
		if (timestamp_ms() > data->death_time)
		{
			print_state(data, dead);
			kill(0, SIGINT);
		}
		usleep(sleep_time);
	}
}

void	run_processes(t_data *data)
{
	pthread_t	death;

	sem_wait(data->start_lock);
	data->start_time = timestamp_ms();
	data->death_time = data->start_time + (uint64_t)data->time_to_die;
	data->state = thinking;
	if (pthread_create(&death, NULL, ft_mortis, (void *)data))
	{
		write(2, "thread creation failed", 22);
		kill(0, SIGINT);
	}
	pthread_detach(death);
	if (data->id % 2 != 0)
		wait_ms(data->time_to_eat / 2, data->num_philos);
	while (data->num_eat != 0)
	{
		if (data->state == thinking)
			eating_state(data);
		else if (data->state == eating)
			sleeping_state(data);
		else if (data->state == sleeping)
			thinking_state(data);
	}
	exit(EXIT_SUCCESS);
}
