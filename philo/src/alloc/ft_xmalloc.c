/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:38:38 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/25 20:28:22 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*ft_xmalloc(size_t size, void (*exit_funct)(char*))
{
	void	*new;

	new = ft_malloc(size);
	if (new == NULL)
		exit_funct("malloc failed\n");
	return (new);
}
