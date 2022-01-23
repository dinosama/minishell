/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 01:44:32 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/21 06:16:09 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '	')
	{
		return (1);
	}
	return (0);
}

int	is_pipe(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
}

int	quote_check(char c, int in_quote)
{
	if (c == '\'')
	{
		if (in_quote == 1)
			return (0);
		if (in_quote == 0)
			return (1);
	}
	if (c == '\"')
	{
		if (in_quote == 2)
			return (0);
		if (in_quote == 0)
			return (2);
	}
	return (in_quote);
}
