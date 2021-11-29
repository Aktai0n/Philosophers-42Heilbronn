/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:21:06 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/29 01:21:58 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

static int	input_correct(int argc, char **argv)
{
	int	i;
	int	j;
	int	index;

	if (argc != 5 && argc != 6)
		return (FALSE);
	i = 1;
	while (argv[i] != NULL)
	{
		index = 0;
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '+')
				return (FALSE);
			if (argv[i][j] == '+')
				index++;
			j++;
		}
		if (index > 1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	convert_input(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->num_eat = ft_atoi(argv[5]);
		if (data->num_eat <= 0)
			return (FALSE);
	}
	else
		data->num_eat = -1;
	if (data->num_philos < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (FALSE);
	return (TRUE);
}

void	init_data(int argc, char **argv, t_data *data)
{
	if (!input_correct(argc, argv))
		ft_exit(data, "Invalid input format");
	if (!convert_input(argc, argv, data))
		ft_exit(data, "Invalid number");
	data->print_lock = sem_open("print_lock", O_CREAT, 0644, 1);
	if (data->print_lock == SEM_FAILED)
		ft_exit(data, "semaphore creation failed");
	data->forks = sem_open("forks", O_CREAT, 0644, data->num_philos);
	if (data->forks == SEM_FAILED)
		ft_exit(data, "semaphore creaton failed");
	data->start_lock = sem_open("start_lock", O_CREAT, 0644, 0);
	if (data->start_lock == SEM_FAILED)
		ft_exit(data, "semaphore creaton failed");
	sem_unlink("print_lock");
	sem_unlink("forks");
	sem_unlink("start_lock");
}
