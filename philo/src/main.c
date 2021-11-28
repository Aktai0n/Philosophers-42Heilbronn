/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:35:28 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/28 18:53:24 by skienzle         ###   ########.fr       */
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
	uint64_t current_time;

	pthread_mutex_lock(print_lock);
	if (philo->data->running == TRUE || state == dead)
	{
		current_time = timestamp_ms() - philo->data->start_time;
		if (state == taking_a_fork)
			printf("%-5llu \e[1;37m%-3d \033[0;33m%s",
				current_time, philo->id, "has taken a fork");
		else if (state == eating)
			printf("%-5llu \e[1;37m%-3d \033[0;32m%s",
				current_time, philo->id, "is eating");
		else if (state == sleeping)
			printf("%-5llu \e[1;37m%-3d \033[0;34m%s",
				current_time, philo->id, "is sleeping");
		else if (state == thinking)
			printf("%-5llu \e[1;37m%-3d \033[0;35m%s",
				current_time, philo->id, "is thinking");
		else if (state == dead)
			printf("%-5llu \e[1;37m%-3d \033[0;31m%s",
				current_time, philo->id, "died");
		printf("\033[0m\n");
	}
	pthread_mutex_unlock(print_lock);
}

void	eating_state(t_philo *philo)
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

void	sleeping_state(t_philo *philo)
{
	philo->state = sleeping;
	print_state(philo, philo->state, &philo->data->print_lock);
	wait_ms(philo->data->time_to_sleep, philo->data->num_philos);
}

void	thinking_state(t_philo *philo)
{
	philo->state = thinking;
	print_state(philo, philo->state, &philo->data->print_lock);
}

t_philo	*init_philo_data(t_data *data)
{
	t_philo	*philo_data;
	int		i;

	philo_data = (t_philo *)ft_calloc(data->num_philos, sizeof(t_philo));
	if (philo_data == NULL)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		philo_data[i].id = i + 1;
		philo_data[i].num_eat = data->max_num_eat;
		philo_data[i].state = thinking;
		philo_data[i].data = data;
		philo_data[i].right_fork = data->forks + i;
		if (i == 0)
			philo_data[i].left_fork = data->forks + (data->num_philos - 1);
		else
			philo_data[i].left_fork = data->forks + (i - 1);
		i++;
	}
	return (philo_data);
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
		wait_ms(philo->data->time_to_die, philo->data->num_philos);
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

int	run_philo(t_data *data)
{
	t_philo		*philo_data;
	pthread_t	death;
	int		i;

	philo_data = init_philo_data(data);
	if (philo_data == NULL)
		return (ft_exit(data, "malloc failed"));
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo_data[i].thread, NULL, philo_loop, (void *)(philo_data + i)))
			return (ft_exit(data, "thread creation failed"));
		usleep(100);
		i++;
	}
	if (pthread_create(&death, NULL, ft_mortis, (void *)philo_data))
		return (ft_exit(data, "thead creation failed"));
	pthread_detach(death);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philo_data[i].thread, NULL);
		i++;
	}
	ft_free_1d((void **)&philo_data);
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	if (init_data(argc, argv, &data))
		return (RETURN_FAILURE);
	if (run_philo(&data))
		return (RETURN_FAILURE);
	destroy_locks(&data);
	ft_freeall();
	return (RETURN_SUCCESS);
}
