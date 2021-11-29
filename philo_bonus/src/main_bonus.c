/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:26:07 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/29 01:24:43 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

uint64_t	timestamp_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	wait_ms(uint64_t ms, int num_processes)
{
	uint64_t	end;

	end = timestamp_ms() + ms;
	while (timestamp_ms() < end)
		usleep(num_processes * 5);
}

void	print_state(t_data *data, const t_state state)
{
	uint64_t	current_time;

	sem_wait(data->print_lock);
	current_time = timestamp_ms() - data->start_time;
	if (state == taking_a_fork)
		printf("%-5llu %-3d %s",
			current_time, data->id, "has taken a fork\n");
	else if (state == eating)
		printf("%-5llu %-3d %s",
			current_time, data->id, "is eating\n");
	else if (state == sleeping)
		printf("%-5llu %-3d %s",
			current_time, data->id, "is sleeping\n");
	else if (state == thinking)
		printf("%-5llu %-3d %s",
			current_time, data->id, "is thinking\n");
	else if (state == dead)
		printf("%-5llu %-3d %s",
			current_time, data->id, "died\n");
	if (state != dead)
		sem_post(data->print_lock);
}

static void	create_philos(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->num_philos)
	{
		pid = fork();
		if (pid == -1)
		{
			write(2, "process creation failed", 23);
			kill(0, SIGINT);
		}
		if (pid == 0)
		{
			data->id = i + 1;
			run_processes(data);
		}
		else
			i++;
	}
	i = -1;
	while (++i < data->num_philos)
		sem_post(data->start_lock);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	init_data(argc, argv, &data);
	create_philos(&data);
	while (waitpid(-1, NULL, 0) != -1)
		usleep(data.num_philos * 50);
	sem_close(data.print_lock);
	sem_close(data.forks);
	sem_close(data.start_lock);
	return (EXIT_SUCCESS);
}
