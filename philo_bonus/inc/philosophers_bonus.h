/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:26:28 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/28 20:13:43 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

/*
** Includes
*/

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>

/*
** Strucures
*/

typedef enum e_state
{
	thinking,
	taking_a_fork,
	eating,
	sleeping,
	dead,
}	t_state;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				id;
	uint64_t		start_time;
	uint64_t		death_time;
	t_state			state;
	sem_t			*forks;
	sem_t			*print_lock;
	sem_t			*start_lock;
}	t_data;

/*
** Prototypes
*/

void	init_data(int argc, char **argv, t_data *data);
void	ft_exit(t_data *data, const char *message);

/*
** Utils
*/

int		ft_atoi(const char *str);
void	ft_putendl_fd(const char *s, int fd);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *ptr, size_t n);

/*
** Defines
*/

# define TRUE 1
# define FALSE 0

#endif