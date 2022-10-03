/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:30:26 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/15 19:43:14 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_in(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*cpy;

	i = 0;
	while (src[i] && i < n)
		i++;
	cpy = malloc(sizeof(char) * (i + 1));
	if ((cpy) == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	ft_word_count(char *str, char *charset)
{
	int	i;
	int	inside;
	int	words;

	i = 0;
	inside = 0;
	words = 0;
	while (str[i])
	{
		if (is_in(str[i], charset) != -1)
			inside = 0;
		else if (inside == 0)
		{
			inside = 1;
			words++;
		}
		i++;
	}
	return (words);
}

char	**ft_split(char *str, char *charset)
{
	char	**split;
	int		i;
	int		length[2];
	int		words;

	words = ft_word_count(str, charset);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	length[0] = 0;
	length[1] = 0;
	while (i < words)
	{
		while (str[length[1]] && is_in(str[length[1]], charset) == -1)
			length[1]++;
		if (length[1] == length[0])
			length[1]++;
		else
			split[i++] = ft_strndup(str + length[0], length[1] - length[0]);
		length[0] = length[1];
	}
	split[i] = 0;
	return (split);
}
