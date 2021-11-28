/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:21:06 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/27 19:37:43 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	input_incorrect(int argc, char **argv)
{
	int	i;
	int	j;
	int	index;

	if (argc != 5 && argc != 6)
		return (RETURN_FAILURE);
	i = 1;
	while (argv[i] != NULL)
	{
		index = 0;
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '+')
				return (RETURN_FAILURE);
			if (argv[i][j] == '+')
				index++;
			j++;
		}
		if (index > 1)
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}

static int	convert_input(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->max_num_eat = ft_atoi(argv[5]);
		if (data->max_num_eat <= 0)
			return (RETURN_FAILURE);
	}
	else
		data->max_num_eat = -1;
	if (data->num_philos < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	if (input_incorrect(argc, argv))
		return (ft_exit(data, "Invalid input format"));
	if (convert_input(argc, argv, data))
		return (ft_exit(data, "Invalid number"));
	data->forks = (pthread_mutex_t *)ft_malloc
					(data->num_philos * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (ft_exit(data, "malloc failed"));
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (ft_exit(data, "mutex initialisation failed"));
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(data->forks + i, NULL))
			return (ft_exit(data, "mutex initialisation failed"));
		i++;
	}
	return (RETURN_SUCCESS);
}
