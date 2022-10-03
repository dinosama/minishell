/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:36:00 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 13:55:52 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i++ < n)
	{
		if (((unsigned char *)s1)[i - 1] != ((unsigned char *)s2)[i - 1])
			return (((unsigned char *)s1)[i - 1]
				- ((unsigned char *)s2)[i - 1]);
	}
	return (0);
}
