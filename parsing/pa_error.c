/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:56:15 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/30 13:25:48 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*get_error(char c, t_cmd *tokens)
{
	if (c == '|')
		ft_putstr_fd("minishell: erreur de syntaxe \
près du symbole inattendu « | »\n", 2);
	if (c == '>')
		ft_putstr_fd("minishell: erreur de syntaxe \
près du symbole inattendu « > »\n", 2);
	if (c == '<')
		ft_putstr_fd("minishell: erreur de syntaxe \
près du symbole inattendu « < »\n", 2);
	if (tokens)
		free_all_cmd(tokens);
	return (NULL);
}

t_checkerror	check_error_two(char *line, t_checkerror e)
{
	if (!ft_whitespace(line[e.i]) && (!is_redirect(line[e.i]) || e.iq)
		&& (!is_pipe(line[e.i]) || e.iq))
		e.cto = 0;
	if (!ft_whitespace(line[e.i]) && (!is_redirect(line[e.i]) || e.iq)
		&& (!is_pipe(line[e.i]) || e.iq))
		e.cti = 0;
	if (!ft_whitespace(line[e.i]) && (!is_pipe(line[e.i]) || e.iq)
		&& (!is_redirect(line[e.i]) || e.iq))
		e.cp = 0;
	if (line[e.i] == '>' && !e.iq)
		e.cto++;
	if (line[e.i] == '<' && !e.iq)
		e.cti++;
	if (line[e.i] == '|' && !e.iq)
		e.cp++;
	return (e);
}

t_cmd	*show_error(t_checkerror e, t_cmd *tokens)
{
	if (e.iq != 0)
	{
		ft_putstr_fd("minishell: erreur: quotes unclosed\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	if (e.cp != 0)
	{
		ft_putstr_fd("minishell: erreur de syntaxe \
près du symbole inattendu « | »\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	if (e.cto != 0)
	{
		ft_putstr_fd("minishell: erreur de syntaxe \
près du symbole inattendu « newline »\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	if (e.cti != 0)
	{
		ft_putstr_fd("minishell: erreur de syntaxe \
près du symbole inattendu « newline »\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	return (tokens);
}

t_cmd	*check_error(char *line, t_cmd *tokens)
{
	t_checkerror	e;

	check_init(&e);
	while (line[e.i])
	{
		e.iq = quote_check(line[e.i], e.iq);
		e = check_error_two(line, e);
		if (e.cti == 3 || e.cto == 3 || e.cp == 2
			|| (line[e.i] == '>' && e.cti != 0)
			|| (line[e.i] == '<' && e.cto != 0)
			|| (line[e.i] == '|' && (e.cto != 0 || e.cti != 0)))
			return (get_error(line[e.i], tokens));
		e.i++;
	}
	tokens = show_error(e, tokens);
	return (tokens);
}

int	go_to_pipe(char *line, int *i, t_cmd *cmd)
{
	int		in_quote;

	in_quote = 0;
	while (line[*i] != 0 && (!is_pipe(line[*i]) || in_quote != 0))
	{
		in_quote = quote_check(line[*i], in_quote);
		*i = *i + 1;
	}
	get_pipe(line, i, cmd);
	cmd->name = NULL;
	return (0);
}
