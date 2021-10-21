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
	static t_malloc	head;

	return (&head);
}

void	*ft_malloc(size_t size)
{
	void		*memory;
	t_malloc	*head;
	t_malloc	*node;

	memory = malloc(size + sizeof(t_malloc));
	if (memory == NULL)
		return (NULL);
	node = memory;
	node->size = size;
	node->next = NULL;
	head = get_malloc_list_head();
	while (head->next != NULL)
		head = head->next;
	head->next = node;
	memory = (t_malloc *)memory + 1;
	return (memory);
}

static void	listclear_malloc(t_malloc **list)
{
	if (list == NULL || *list == NULL)
		return ;
	listclear_malloc(&(*list)->next);
	free(*list);
	*list = NULL;
}

void	ft_freeall(void)
{
	t_malloc	*head;

	head = get_malloc_list_head();
	listclear_malloc(&head->next);
}

void	ft_free(void *ptr)
{
	t_malloc	*node;
	t_malloc	*prev;

	if (ptr == NULL)
		return ;
	ptr = (t_malloc *)ptr - 1;
	prev = get_malloc_list_head();
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
	*to_free = NULL;
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
	printf("%p\n", test);
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
	ft_freeall();
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
			test[i][j] = 10;
			printf("%d", test[i][j]);
		}
		printf(" %p\n", test[i]);
	}
	printf("%p\n", test);
	// ft_free_2d((void ***)&test);
	ft_freeall();
	// system("leaks philo");
	return (0);
}