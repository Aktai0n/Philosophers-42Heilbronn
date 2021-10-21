/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:35:28 by skienzle          #+#    #+#             */
/*   Updated: 2021/10/21 19:32:11 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

typedef struct s_malloc
{
	struct s_malloc	*head;
	size_t			size;
	struct s_malloc	*next;
}	t_malloc;

t_malloc	*get_malloc_list_head(void)
{
	static t_malloc	*head = NULL;
	if (head == NULL)
		head = malloc(sizeof(t_malloc));
	if (head == NULL)
		return (NULL);
	return (head);
}

static void malloc_lstadd_back(t_malloc **list, t_malloc *to_add)
{
	t_malloc	*temp;

	if (list == NULL || to_add == NULL)
		return ;
	if (*list == NULL)
	{
		*list = to_add;
		return ;
	}
	temp = *list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = to_add;
}

void	*ft_malloc(size_t size)
{
	void			*memory;
	t_malloc		*head;
	t_malloc		*node;

	memory = malloc(size + sizeof(t_malloc));
	if (memory == NULL)
		return (NULL);
	head = get_malloc_list_head();
	if (head == NULL)
		return (NULL);
	node = memory;
	node->size = size;
	node->next = NULL;
	malloc_lstadd_back(&head->next, node);
	memory = (t_malloc *)memory + 1;
	return (memory);
}

static void	malloc_listclear(t_malloc *list)
{
	t_malloc	*temp;

	printf("%p\n", list);
	if (list == NULL || list == NULL)
		return ;
	malloc_listclear(list->next);
	printf("afterwards =%p\n", list);
	free(list);
}

void	ft_freeall(void)
{
	void		*temp;
	t_malloc	*head;

	head = get_malloc_list_head();
	if (head == NULL)
		return ;
	malloc_listclear(head->next);
	free(head);
}

void	ft_free(void *ptr)
{
	t_malloc	*head;
	t_malloc	*node;
	t_malloc	*prev;

	head = get_malloc_list_head();
	if (ptr == NULL || head == NULL)
		return ;
	ptr = (t_malloc *)ptr - 1;
	node = head->next;
	prev = node;
	while (node->next != NULL && node != ptr)
	{
		prev = node;
		node = node->next;
	}
	if (ptr == node)
		head->next = node->next;
	prev->next = node->next;
	free(ptr);
	ptr = NULL;
	if (head->next == NULL)
	{
		free(head);
		head = NULL;
	}
}

void	ft_free_2d(void ***to_free)
{
	int	i;

	if (*to_free == NULL)
		return ;
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

	test = (int **)ft_malloc(10 * sizeof(*test));
	for (int i = 0; i < 10; i++)
	{
		test[i] = (int *)ft_malloc(50 * sizeof(**test));
		bzero(test[i], 50 * sizeof(**test));
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			// test[i][j] = 10;
			printf("%d", test[i][j]);
		}
		printf(" %p\n", test[i]);
	}
	// ft_freeall();
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
	system("leaks philo");
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_data data;
	
// 	if (argc != 5 && argc != 6)
// 		return (1);
// 	return (0);
// }