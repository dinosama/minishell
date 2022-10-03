/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:50:39 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/27 15:52:44 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	b;
	unsigned long	l;

	i = 0;
	b = 0;
	while (dest[i])
		i++;
	l = 0;
	while (src[l])
		l++;
	if (size <= i)
		l += size;
	else
		l += i;
	while (src[b] && i + b + 1 < size)
	{
		dest[i + b] = src[b];
		b++;
	}
	dest[i + b] = '\0';
	return (l);
}
