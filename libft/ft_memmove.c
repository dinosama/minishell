/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:43:24 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 13:46:11 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned long	i;
	char			*p;

	i = 0;
	p = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		while (i++ < len)
			p[i - 1] = ((char *)src)[i - 1];
	}
	else
		while (len--)
			p[len] = ((char *)src)[len];
	return (dst);
}
