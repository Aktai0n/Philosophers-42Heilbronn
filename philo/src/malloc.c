/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:03:48 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/27 15:33:07 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

t_alloc	*get_alloc_list_head(void)
{
	static t_alloc	head;

	return (&head);
}

void	*ft_malloc(size_t size)
{
	void	*memory;
	t_alloc	*head;
	t_alloc	*node;

	memory = malloc(size + sizeof(t_alloc));
	if (memory == NULL)
		return (NULL);
	node = memory;
	node->size = size;
	node->next = NULL;
	head = get_alloc_list_head();
	while (head->next != NULL)
		head = head->next;
	head->next = node;
	memory = (t_alloc *)memory + 1;
	return (memory);
}

void	ft_bzero(void *ptr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)ptr)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*memory;
	size_t	tot_size;

	tot_size = nitems * size;
	memory = ft_malloc(tot_size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, tot_size);
	return (memory);
}
