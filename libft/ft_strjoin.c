/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:37:13 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 13:44:33 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i++])
		;
	j = 0;
	while (s2[j++])
		;
	res = malloc(i + j - 1);
	if (res == NULL)
		return (NULL);
	res[i + j - 2] = '\0';
	while (--j)
		res[i + j - 2] = s2[j - 1];
	while (--i)
		res[i - 1] = s1[i - 1];
	return (res);
}
