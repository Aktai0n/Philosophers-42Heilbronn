/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:02:03 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/26 21:50:35 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;
	t_alloc	*node;

	if (ptr == NULL)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	new = ft_malloc(size);
	if (new == NULL)
	{
		ft_free(ptr);
		return (NULL);
	}
	node = (t_alloc *)ptr - 1;
	if (node->size < size)
		ft_memcpy(new, ptr, node->size);
	else
		ft_memcpy(new, ptr, size);
	ft_free(ptr);
	return (new);
}
