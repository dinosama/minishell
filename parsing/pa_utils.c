/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 02:04:28 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/23 04:56:48 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

char	*ft_substr(char *s, int start, int len)
{
	int				i;
	unsigned int	n;
	char			*str;

	if (!s)
		return (0);
	n = (unsigned int)start;
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (i < len && s[i] && n < ft_strlen(s))
	{
		str[i] = s[n];
		n++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	calcul_arg(char *line, int i)
{
	int		arg;
	int		in_quote;
	int		in_word;

	arg = 0;
	in_quote = 0;
	in_word = 0;
	while (line[i] && (!is_pipe(line[i]) || in_quote != 0)
		&& (!is_redirect(line[i]) || in_quote != 0))
	{
		in_quote = quote_check(line[i], in_quote);
		if (!whitespace(line[i]) && !in_word)
			in_word = 1;
		if (whitespace(line[i]) && in_word && !in_quote)
		{
			in_word = 0;
			arg++;
		}
		i++;
	}
	if (in_word == 1)
		arg++;
	return (arg);
}
