/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:23:16 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/25 17:56:31 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	value;
	long int	signe;

	value = 0;
	signe = 1;
	i = 0;
	while (*(str + i) == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe *= -1;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
		{
			errno = ERANGE;
			break ;
		}
		value = value * 10 + str[i] - 48;
		i++;
	}
	return ((int)(value * signe));
}
