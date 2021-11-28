/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:26:07 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/28 20:37:10 by skienzle         ###   ########.fr       */
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
		printf("%-5llu \e[1;37m%-3d \033[0;33m%s",
			current_time, data->id, "has taken a fork");
	else if (state == eating)
		printf("%-5llu \e[1;37m%-3d \033[0;32m%s",
			current_time, data->id, "is eating");
	else if (state == sleeping)
		printf("%-5llu \e[1;37m%-3d \033[0;34m%s",
			current_time, data->id, "is sleeping");
	else if (state == thinking)
		printf("%-5llu \e[1;37m%-3d \033[0;35m%s",
			current_time, data->id, "is thinking");
	else if (state == dead)
		printf("%-5llu \e[1;37m%-3d \033[0;31m%s",
			current_time, data->id, "died");
	printf("\033[0m\n");
	sem_post(data->print_lock);
}

void	eating_state(t_data *data)
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
	wait_ms(data->time_to_eat, data->num_philos);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	sleeping_state(t_data *data)
{
	data->state = sleeping;
	print_state(data, data->state);
	wait_ms(data->time_to_sleep, data->num_philos);
}

void	thinking_state(t_data *data)
{
	data->state = thinking;
	print_state(data, data->state);
}

void	run_processes(t_data *data)
{
	sem_wait(data->start_lock);
	data->start_time = timestamp_ms();
	data->death_time = data->start_time + data->time_to_die;
	data->state = thinking;
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

void	create_philos(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->num_philos)
	{
		pid = fork();
		if (pid == -1)
		{
			kill(-1, SIGINT);
			ft_exit(data, "process creation failed");
		}
		if (pid == 0)
		{
			data->id = i + 1;
			run_processes(data);
		}
		else
			i++;
	}
	wait_ms(data->time_to_sleep, data->num_philos);
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
		continue ;
	sem_close(data.print_lock);
	sem_close(data.forks);
	sem_close(data.start_lock);
	return (EXIT_SUCCESS);
}