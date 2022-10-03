/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:55:09 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 13:49:44 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*p;

	if (src == NULL && dst == NULL)
		return (NULL);
	p = dst;
	while (n--)
		p[n] = ((char *)src)[n];
	return (dst);
}
