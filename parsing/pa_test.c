/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 01:41:49 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/12 13:41:41 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	show_red(t_cmd *tokens)
{
	if (tokens->i_red)
	{
		ft_putstr("file: ");
		ft_putstr(tokens->i_red->file);
		ft_putstr("\n");
		ft_putstr("type: ");
		ft_putchar(tokens->i_red->type + 48);
		ft_putstr("\n");
	}
	if (tokens->o_red)
	{
		ft_putstr("file: ");
		ft_putstr(tokens->o_red->file);
		ft_putstr("\n");
		ft_putstr("type: ");
		ft_putchar(tokens->o_red->type + 48);
		ft_putstr("\n");
	}
}

void	show_tokens(t_cmd *tokens)
{
	int		i;

	i = 0;
	while (tokens != NULL)
	{
		ft_putstr("___________________\n");
		ft_putstr("name: ");
		ft_putstr(tokens->name);
		ft_putstr("\n");
		while (tokens->args[i] != NULL)
		{
			ft_putstr("argv: ");
			ft_putstr(tokens->args[i]);
			ft_putstr("\n");
			i++;
		}
		ft_putstr("pipe: ");
		ft_putchar(tokens->pipe + 48);
		ft_putstr("\n");
		show_red(tokens);
		ft_putstr("___________________\n");
		i = 0;
		tokens = tokens->next;
	}
}
