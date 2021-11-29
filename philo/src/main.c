/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:35:28 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/29 01:28:56 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	wait_for_philos(t_philo *philo_data, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_join(philo_data[i].thread, NULL);
		i++;
	}
}

int	run_philo(t_data *data)
{
	t_philo		*philo_data;
	pthread_t	death;
	int			i;

	philo_data = init_philo_data(data);
	if (philo_data == NULL)
		return (ft_exit(data, "malloc failed"));
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo_data[i].thread, NULL,
				philo_loop, (void *)(philo_data + i)))
			return (ft_exit(data, "thread creation failed"));
		usleep(100);
		i++;
	}
	if (pthread_create(&death, NULL,
			ft_mortis, (void *)philo_data))
		return (ft_exit(data, "thead creation failed"));
	pthread_detach(death);
	wait_for_philos(philo_data, data->num_philos);
	ft_free_1d((void **)&philo_data);
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (init_data(argc, argv, &data))
		return (RETURN_FAILURE);
	if (run_philo(&data))
		return (RETURN_FAILURE);
	destroy_locks(&data);
	ft_freeall();
	return (RETURN_SUCCESS);
}
