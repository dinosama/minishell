/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:21:12 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 13:56:21 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*dst;
	unsigned long	i;

	i = 0;
	dst = malloc(count * size);
	if (dst == NULL)
		return (NULL);
	while (i++ < size * count)
		((char *)dst)[i - 1] = 0;
	return (dst);
}
