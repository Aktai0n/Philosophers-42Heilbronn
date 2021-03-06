/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:52:24 by skienzle          #+#    #+#             */
/*   Updated: 2021/11/29 01:32:55 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <stdlib.h>

typedef struct s_alloc
{
	size_t			size;
	struct s_alloc	*next;
}	t_alloc;

t_alloc		*get_alloc_list_head(void);
void		ft_freeall(void);
void		*ft_malloc(size_t size);
void		ft_free(void *ptr);
void		*ft_calloc(size_t nitems, size_t size);
void		ft_free_1d(void **to_free);
void		ft_free_2d(void ***to_free);

void		ft_putendl_fd(char *s, int fd);

#endif