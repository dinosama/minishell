/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:18:48 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 15:08:54 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizefinder(long *n)
{
	long	dix;
	int		size;

	size = 0;
	dix = 1;
	if (*n <= 0)
	{
		*n *= -1;
		size++;
	}
	while (*n / dix > 0)
	{
		dix *= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	dix;
	long	n2;
	int		size;
	char	*nbr;

	n2 = (long)n;
	size = sizefinder(&n2);
	nbr = malloc(size + 1);
	if (nbr == NULL)
		return (NULL);
	nbr[size] = '\0';
	dix = 10;
	if (n == 0)
		nbr[--size] = '0';
	while (n2 > 0)
	{
		nbr[--size] = n2 % dix + '0';
		n2 = n2 / dix;
	}
	if (size == 1)
		nbr[--size] = '-';
	return (nbr);
}
