/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:53:09 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 13:24:32 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	res = malloc(i + 1);
	if (res == NULL)
		return (NULL);
	res[i] = '\0';
	while (i--)
		res[i] = f(i, s[i]);
	return (res);
}
