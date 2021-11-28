/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:56:02 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/27 15:30:54 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

void	ft_free(void *ptr)
{
	t_alloc	*node;
	t_alloc	*prev;

	if (ptr == NULL)
		return ;
	ptr = (t_alloc *)ptr - 1;
	prev = get_alloc_list_head();
	node = prev->next;
	while (node->next != NULL && node != ptr)
	{
		prev = node;
		node = node->next;
	}
	if (node == ptr)
	{
		prev->next = node->next;
		free(ptr);
	}
	else
		ft_putendl_fd("ptr does not occur in the alloc list", 2);
}

void	ft_freeall(void)
{
	t_alloc	*list;
	t_alloc	*temp;

	temp = get_alloc_list_head();
	list = temp->next;
	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp);
		temp = NULL;
	}
}

void	ft_free_1d(void **to_free)
{
	if (to_free == NULL || *to_free == NULL)
		return ;
	ft_free(*to_free);
	*to_free = NULL;
}

void	ft_free_2d(void ***to_free)
{
	size_t	i;

	if (to_free == NULL || *to_free == NULL)
		return ;
	i = 0;
	while ((*to_free)[i] != NULL)
	{
		ft_free((*to_free)[i]);
		(*to_free)[i] = NULL;
		i++;
	}
	ft_free(*to_free);
	*to_free = NULL;
}
