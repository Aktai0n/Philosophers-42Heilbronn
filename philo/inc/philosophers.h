/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:36:00 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/28 23:32:34 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*
** Includes
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

/*
** Structures
*/

typedef enum u_state
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
	int				max_num_eat;
	int				running;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				num_eat;
	t_state			state;
	uint64_t		death_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

/*
** Prototypes
*/

int			init_data(int argc, char **argv, t_data *data);
t_philo		*init_philo_data(t_data *data);

void		*philo_loop(void *attr);
void		*ft_mortis(void *attr);

uint64_t	timestamp_ms(void);
void		wait_ms(uint64_t ms, int num_threads);
void		print_state(const t_philo *philo, const t_state state,
				pthread_mutex_t *print_lock);

int			ft_exit(t_data *data, const char *message);
void		destroy_locks(t_data *data);

/*
** Utils
*/

size_t		ft_strlen(const char *str);
int			ft_isdigit(int c);
void		ft_putendl_fd(const char *s, int fd);
int			ft_atoi(const char *str);

void		*ft_malloc(size_t size);
void		*ft_calloc(size_t nitems, size_t size);
void		ft_free(void *ptr);
void		ft_freeall(void);
void		ft_free_1d(void **to_free);
void		ft_free_2d(void ***to_free);

/*
** Defines
*/

# define TRUE 1
# define FALSE 0
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

#endif