/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:03:48 by skienzle          #+#    #+#             */
/*   Updated: 2021/10/21 20:14:00 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

typedef struct s_malloc
{
	size_t			size;
	struct s_malloc	*next;
}	t_malloc;

static t_malloc	*get_malloc_list_head(void)
{
	static t_malloc	*head = NULL;

	if (head == NULL)
		head = malloc(sizeof(t_malloc));
	if (head == NULL)
		return (NULL);
	return (head);
}

void	*ft_malloc(size_t size)
{
	void		*memory;
	t_malloc	*head;
	t_malloc	*node;

	head = get_malloc_list_head();
	if (head == NULL)
		return (NULL);
	memory = malloc(size + sizeof(t_malloc));
	if (memory == NULL)
		return (NULL);
	node = memory;
	node->size = size;
	node->next = NULL;
	while (head->next != NULL)
		head = head->next;
	head->next = node;
	memory = (t_malloc *)memory + 1;
	return (memory);
}

void	ft_freeall(void)
{
	t_malloc	*list;

	list = get_malloc_list_head();
	while (list != NULL)
	{
		free(list);
		list = list->next;
	}
}

void	ft_free(void *ptr)
{
	t_malloc	*node;
	t_malloc	*prev;

	prev = get_malloc_list_head();
	if (ptr == NULL || prev == NULL)
		return ;
	ptr = (t_malloc *)ptr - 1;
	node = prev->next;
	while (node->next != NULL && node != ptr)
	{
		prev = node;
		node = node->next;
	}
	prev->next = node->next;
	free(ptr);
}

void	ft_free_2d(void ***to_free)
{
	int	i;

	if (*to_free == NULL)
		return ;
	i = 0;
	while ((*to_free)[i] != NULL)
	{
		ft_free((*to_free)[i]);
		i++;
	}
	ft_free(*to_free);
}

int	main(void)
{
	int	**test;

	test = (int **)ft_malloc(11 * sizeof(*test));
	for (int i = 0; i < 10; i++)
	{
		test[i] = (int *)ft_malloc(50 * sizeof(**test));
		bzero(test[i], 50 * sizeof(**test));
	}
	test[10] = NULL;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			// test[i][j] = 10;
			printf("%d", test[i][j]);
		}
		printf(" %p\n", test[i]);
	}
	ft_free_2d((void ***)&test);
	// test = (int **)ft_malloc(10 * sizeof(*test));
	// for (int i = 0; i < 10; i++)
	// {
	// 	test[i] = (int *)ft_malloc(50 * sizeof(**test));
	// 	bzero(test[i], 50 * sizeof(**test));
	// }
	// for (int i = 0; i < 10; i++)
	// {
	// 	for (int j = 0; j < 50; j++)
	// 	{
	// 		test[i][j] = 10;
	// 		printf("%d %p ", test[i][j], test[i]);
	// 	}
	// 	printf("\n");
	// }
	ft_freeall();
	system("leaks philo");
	return (0);
}